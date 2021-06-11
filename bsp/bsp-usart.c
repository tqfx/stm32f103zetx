/*!
 @file           bsp-usart.c
 @brief          bsp for usart
 @author         tqfx tqfx@foxmail.com
 @version        0
 @date           2021-06-10
 @copyright      Copyright (C) 2021 tqfx
 \n \n
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 \n \n
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 \n \n
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#include "bsp-usart.h"

#include "main.h"

#include <stdarg.h>
#include <stdio.h>

uint8_t os_buf8[2][BUFSIZ_OS];
uint8_t *os_buf = *os_buf8;

#define BUFSIZ32 128
#define BUFSIZ16 (BUFSIZ32 << 1)
#define BUFSIZ8  (BUFSIZ32 << 2)

static va_list ap;
static float buf32[BUFSIZ32];
static uint8_t *pn = (uint8_t *)buf32;

#define FLAG_TX_DMA (1 << 0)
#define FLAG_RX_BUF (1 << 1)
static int8_t flag = 0x00;

void usart_disable(UART_HandleTypeDef *huart)
{
    /* Disable UART */
    __HAL_UART_DISABLE(huart);
}

void usart_enable(UART_HandleTypeDef *huart)
{
    /* Enable UART */
    __HAL_UART_ENABLE(huart);
}

void usart_dma_rerx(UART_HandleTypeDef *huart,
                    uint16_t len)
{
    /* Disable UART */
    __HAL_UART_DISABLE(huart);

    do
    {
        /* Disable the specified DMA Stream */
        __HAL_DMA_DISABLE(huart->hdmarx);
    } while (huart->hdmarx->Instance->CCR & DMA_CCR_EN);

    /* Clear all flag */
    BSP_DMA_CLEAR_FLAG(huart->hdmarx);

    /* DMA stream x number of data register */
    huart->hdmarx->Instance->CNDTR = len;

    /* Enable the specified DMA Stream */
    __HAL_DMA_ENABLE(huart->hdmarx);
    /* Enable UART */
    __HAL_UART_ENABLE(huart);
}

void usart_dma_retx(UART_HandleTypeDef *huart,
                    uint16_t len)
{
    /* Disable UART */
    __HAL_UART_DISABLE(huart);

    do
    {
        /* Disable the specified DMA Stream */
        __HAL_DMA_DISABLE(huart->hdmatx);
    } while (huart->hdmatx->Instance->CCR & DMA_CCR_EN);

    /* Clear all flag */
    BSP_DMA_CLEAR_FLAG(huart->hdmatx);

    /* DMA stream x number of data register */
    huart->hdmatx->Instance->CNDTR = len;

    /* Enable the specified DMA Stream */
    __HAL_DMA_ENABLE(huart->hdmatx);
    /* Enable UART */
    __HAL_UART_ENABLE(huart);
}

void usart_dma_rx_init(UART_HandleTypeDef *huart)
{
    /* DMA Enable Receiver */
    SET_BIT(huart->Instance->CR3, USART_CR3_DMAR);

    /* Enable UART */
    __HAL_UART_ENABLE(huart);
    /* Enalbe idle interrupt */
    __HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);

    do
    {
        /* Disable the specified DMA Stream */
        __HAL_DMA_DISABLE(huart->hdmarx);
    } while (huart->hdmarx->Instance->CCR & DMA_CCR_EN);

    /* Clear all flag */
    BSP_DMA_CLEAR_FLAG(huart->hdmarx);

    /* DMA stream x peripheral address register */
    huart->hdmarx->Instance->CPAR = (uint32_t) & (huart->Instance->DR);
}

void usart_dma_tx_init(UART_HandleTypeDef *huart)
{
    /* DMA Enable Transmitter */
    SET_BIT(huart->Instance->CR3, USART_CR3_DMAT);

    /* Enable UART */
    __HAL_UART_ENABLE(huart);
    /* Enable transmission complete interrupt */
    __HAL_UART_ENABLE_IT(huart, UART_IT_TC);

    do
    {
        /* Disable the specified DMA Stream */
        __HAL_DMA_DISABLE(huart->hdmatx);
    } while (huart->hdmatx->Instance->CCR & DMA_CCR_EN);

    /* Clear all flag */
    BSP_DMA_CLEAR_FLAG(huart->hdmatx);

    /* DMA stream x peripheral address register */
    huart->hdmatx->Instance->CPAR = (uint32_t) & (huart->Instance->DR);
}

void usart_dma_init(UART_HandleTypeDef *huart)
{
    /* DMA Enable Receiver and Transmitter */
    usart_dma_rx_init(huart);
    usart_dma_tx_init(huart);
}

void usart_dma_rx(UART_HandleTypeDef *huart,
                  uint8_t *buf,
                  uint16_t len)
{
    do
    {
        /* Disable the specified DMA Stream */
        __HAL_DMA_DISABLE(huart->hdmarx);
    } while (huart->hdmarx->Instance->CCR & DMA_CCR_EN);

    /* Clear all flag */
    BSP_DMA_CLEAR_FLAG(huart->hdmarx);

    /* DMA stream x memory address register   */
    huart->hdmarx->Instance->CMAR = (uint32_t)(buf);
    /* DMA stream x number of data register */
    huart->hdmarx->Instance->CNDTR = len;

    /* Enable the specified DMA Stream */
    __HAL_DMA_ENABLE(huart->hdmarx);
}

void usart_dma_tx(UART_HandleTypeDef *huart,
                  uint8_t *data,
                  uint16_t len)
{
    do
    {
        /* Disable the specified DMA Stream */
        __HAL_DMA_DISABLE(huart->hdmatx);
    } while (huart->hdmatx->Instance->CCR & DMA_CCR_EN);

    /* Clear all flag */
    BSP_DMA_CLEAR_FLAG(huart->hdmatx);

    /* DMA stream x memory 0 address register   */
    huart->hdmatx->Instance->CMAR = (uint32_t)(data);
    /* DMA stream x number of data register */
    huart->hdmatx->Instance->CNDTR = len;

    /* Enable the specified DMA Stream */
    __HAL_DMA_ENABLE(huart->hdmatx);
}

void dma_printf(const char *fmt, ...)
{
    va_start(ap, fmt);
    uint16_t n = (uint16_t)vsprintf((char *)pn + 2, fmt, ap);
    va_end(ap);

    if (n)
    {
        uint8_t *p = pn + 2;
        uint8_t *buf = (uint8_t *)buf32;

        pn[0] = (uint8_t)n;
        pn[1] = (uint8_t)(n >> 8);

        if (pn == buf)
        {
            SET_BIT(flag, FLAG_TX_DMA);
            usart_dma_tx(&huart_os, p, n);
        }

        pn = p + n;
        if (pn - buf > BUFSIZ8 - 2)
        {
            pn = buf;
        }
    }
}

static void dma_printf_irq(void)
{
    static uint8_t *pi = (uint8_t *)buf32;

    uint16_t n = (uint16_t)(pi[0] + ((uint16_t)pi[1] << 8));
    uint8_t *p = pi + 2 + n;

    pi[0] = pi[1] = 0;
    if (p < pn)
    {
        pi = p;
        SET_BIT(flag, FLAG_TX_DMA);
        usart_dma_tx(&huart_os, p + 2, n);
    }
    else
    {
        pi = pn = (uint8_t *)buf32;
        CLEAR_BIT(flag, FLAG_TX_DMA);
    }
}

/**
 * @brief This function handles USART global interrupt.
*/
void PC_IRQHandler(void)
{
    if (huart_os.Instance->SR & UART_FLAG_RXNE) /*!< USART Status register*/
    {
        __HAL_UART_CLEAR_PEFLAG(&huart_os); /* Clears the UART PE pending flag */
    }
    else if (huart_os.Instance->SR & UART_FLAG_TC)
    {
        __HAL_UART_CLEAR_FLAG(&huart_os, UART_FLAG_TC);

        if (READ_BIT(flag, FLAG_TX_DMA))
        {
            dma_printf_irq();
        }
    }
    else if (huart_os.Instance->SR & UART_FLAG_IDLE)
    {
        __HAL_UART_CLEAR_PEFLAG(&huart_os); /* Clears the UART PE pending flag */

        if (READ_BIT(flag, FLAG_RX_BUF))
        {
            /* Current memory buffer used is Memory 1 */

            __HAL_DMA_DISABLE(huart_os.hdmarx);

            os_buf = os_buf8[1];
            os_buf[0] = (uint8_t)(BUFSIZ_OS - 1 - huart_os.hdmarx->Instance->CNDTR);

            huart_os.hdmarx->Instance->CMAR = (uint32_t)(os_buf8[0] + 1);
            huart_os.hdmarx->Instance->CNDTR = BUFSIZ_OS - 1;

            CLEAR_BIT(flag, FLAG_RX_BUF);

            __HAL_DMA_ENABLE(huart_os.hdmarx);
        }
        else
        {
            /* Current memory buffer used is Memory 0 */

            __HAL_DMA_DISABLE(huart_os.hdmarx);

            os_buf = os_buf8[0];
            os_buf[0] = (uint8_t)(BUFSIZ_OS - 1 - huart_os.hdmarx->Instance->CNDTR);

            huart_os.hdmarx->Instance->CMAR = (uint32_t)(os_buf8[1] + 1);
            huart_os.hdmarx->Instance->CNDTR = BUFSIZ_OS - 1;

            SET_BIT(flag, FLAG_RX_BUF);

            __HAL_DMA_ENABLE(huart_os.hdmarx);
        }
    }
}

void os_printf(const char *format, ...)
{
    va_start(ap, format);
    uint16_t n = (uint16_t)vsprintf((char *)buf32, format, ap);
    va_end(ap);

    /* USART transmit by DMA Stream */
    usart_dma_tx(&huart_os, (uint8_t *)buf32, n);

    /* Wait Complete Transmit flag to be set */
    BSP_DMA_WAIT_TC(huart_os.hdmatx);
}

void os_justfloat(uint8_t n, ...)
{
    float *p = buf32;
    float *d = buf32 + n;

    va_start(ap, n);
    while (p != d)
    {
        *p++ = (float)va_arg(ap, double);
    }
    *p = 1.0F / 0.0F;
    va_end(ap);

    /* USART transmit by DMA Stream */
    usart_dma_tx(&huart_os, (uint8_t *)buf32, (uint16_t)(sizeof(float) * (n + 1U)));

    /* Wait Complete Transmit flag to be set */
    BSP_DMA_WAIT_TC(huart_os.hdmatx);
}

/* END OF FILE */
