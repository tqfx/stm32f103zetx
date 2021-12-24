/*!
 @file pc.c
 @brief pc
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "pc.h"

static buf_u pc_rx[2];
static buf_u pc_tx[1];

static struct
{
  uint8_t *buf0;
  uint8_t *buf1;
} stat[1] = {{
  .buf0 = pc_rx[0].u,
  .buf1 = pc_rx[1].u,
}};

void pc_init(void)
{
  stat->buf0 = pc_rx[0].u;
  stat->buf1 = pc_rx[1].u;
  uart_dma_init(&hpc);
  uart_dma_rx(&hpc, stat->buf0 + 1, PC_BUFSIZ - 1);
}

#include <stdio.h>
#include <stdarg.h>

void pc_printf(const char *fmt, ...)
{
  va_list ap;
  char *p = pc_tx->s;

  va_start(ap, fmt);
  uint8_t n = (uint8_t)vsnprintf(p, PC_BUFSIZ, fmt, ap);
  va_end(ap);

  /* USART transmit by DMA Stream */
  uart_dma_tx(&hpc, p, n);
  /* Wait Complete Transmit flag to be set */
  BSP_DMA_WAIT_TC(hpc.hdmatx);
}

void pc_justfloat(uint8_t n, ...)
{
  va_list ap;
  float *p = pc_tx->f;
  float *q = p + n;

  va_start(ap, n);
  while (p != q)
  {
    *p++ = (float)va_arg(ap, double);
  }
  *p = (1.0F / 0.0F);
  va_end(ap);

  /* USART transmit by DMA Stream */
  uart_dma_tx(&hpc, pc_tx->u, (uint16_t)(sizeof(float) * (n + 1)));
  /* Wait Complete Transmit flag to be set */
  BSP_DMA_WAIT_TC(hpc.hdmatx);
}

#include "exec.h"

/**
 * @brief This function handles USART global interrupt.
*/
void PC_IRQHandler(void)
{
  /* USART Status register */
  if (hpc.Instance->SR & UART_FLAG_RXNE)
  {
    __HAL_UART_CLEAR_PEFLAG(&hpc); /* Clears the UART PE pending flag */
  }
  else if (hpc.Instance->SR & UART_FLAG_IDLE)
  {
    __HAL_UART_CLEAR_PEFLAG(&hpc); /* Clears the UART PE pending flag */

    __HAL_DMA_DISABLE(hpc.hdmarx);
    if (READ_BIT(exec->uart, PC_RXBF_MSK))
    {
      /* Current memory buffer used is Memory 1 */
      exec->pc = stat->buf1;
      exec->pc[0] = (uint8_t)(PC_BUFSIZ - 1 - hpc.hdmarx->Instance->CNDTR);

      hpc.hdmarx->Instance->CMAR = (size_t)(stat->buf0 + 1);
      hpc.hdmarx->Instance->CNDTR = PC_BUFSIZ - 1;

      CLEAR_BIT(exec->uart, PC_RXBF_MSK);
    }
    else
    {
      /* Current memory buffer used is Memory 0 */
      exec->pc = stat->buf0;
      exec->pc[0] = (uint8_t)(PC_BUFSIZ - 1 - hpc.hdmarx->Instance->CNDTR);

      hpc.hdmarx->Instance->CMAR = (size_t)(stat->buf1 + 1);
      hpc.hdmarx->Instance->CNDTR = PC_BUFSIZ - 1;

      SET_BIT(exec->uart, PC_RXBF_MSK);
    }
    __HAL_DMA_ENABLE(hpc.hdmarx);

    SET_BIT(exec->uart, PC_RXEN_MSK);
  }
  else if (hpc.Instance->SR & UART_FLAG_TC)
  {
    __HAL_UART_CLEAR_FLAG(&hpc, UART_FLAG_TC);
  }
}

/* END OF FILE */
