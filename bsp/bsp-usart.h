/*!
 @file           bsp-usart.h
 @brief          bsp fo usart
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

/* Define to prevent recursive inclusion */
#ifndef __BSP_USART_H__
#define __BSP_USART_H__

#include "bsp.h"

#include "main.h"

#include <stdint.h>

#define huart_os huart1 /* usart, connect to the upper computer */
#undef PC_IRQHandler
#define PC_IRQHandler USART1_IRQHandler

extern UART_HandleTypeDef huart_os;

#define BUFSIZ_OS 256U
extern uint8_t *os_buf;

__BEGIN_DECLS

/**
 * @brief        Disable USART
 * @param[in]    huart: UART handle Structure pointer
*/
extern void usart_disable(UART_HandleTypeDef *huart);

/**
 * @brief        Enable USART
 * @param[in]    huart: UART handle Structure pointer
*/
extern void usart_enable(UART_HandleTypeDef *huart);

/**
 * @brief        Restart USART DMA receiver
 * @param[in]    huart: UART handle Structure pointer
 * @param[in]    len:   the length of data
*/
extern void usart_dma_rerx(UART_HandleTypeDef *huart,
                           uint16_t len);

/**
 * @brief        Restart USART DMA transmit
 * @param[in]    huart: UART handle Structure pointer
 * @param[in]    len:   the length of data
*/
extern void usart_dma_retx(UART_HandleTypeDef *huart,
                           uint16_t len);

/**
 * @brief        Initializes USART DMA receiver
 * @param[in]    huart: UART handle Structure pointer
*/
extern void usart_dma_rx_init(UART_HandleTypeDef *huart);

/**
 * @brief        Initializes USART DMA transmit
 * @param[in]    huart: UART handle Structure pointer
*/
extern void usart_dma_tx_init(UART_HandleTypeDef *huart);

/**
 * @brief        Initializes USART DMA receiver and transmit
 * @param[in]    huart: UART handle Structure pointer
*/
extern void usart_dma_init(UART_HandleTypeDef *huart);

/**
 * @brief        Enable double memory buffer
 * @param[in]    huart: UART handle Structure pointer
 * @param[in]    buf:   DMA stream x memory 0 address register
 * @param[in]    len:   DMA stream x number of data register
*/
extern void usart_dma_rx(UART_HandleTypeDef *huart,
                         uint8_t *buf,
                         uint16_t len);

/**
 * @brief        USART transmit by DMA Stream
 * @param[in]    huart: UART handle Structure pointer
 * @param[in]    data:  the address of data
 * @param[in]    len:   the length of data
*/
extern void usart_dma_tx(UART_HandleTypeDef *huart,
                         uint8_t *data,
                         uint16_t len);

extern void dma_printf(const char *fmt, ...);

/**
 * @brief        print string to USART
 * @param[in]    format: printf format
*/
extern void os_printf(const char *format, ...);

/**
 * @brief        print float data to USART by little-endian mode
 * @param[in]    n: number of float data
 * @param[in]    ...: float data
*/
extern void os_justfloat(uint8_t n, ...);

/**
 * @brief        push float data to buffer by little-endian mode
 * @param[in]    f: float data
*/
extern void os_pushf(float f);

/**
 * @brief        print float and tail data to USART by little-endian mode
*/
extern void os_tail(void);

/**
 * @brief        print float to USART
 * @param[in]    x: float number
 * @param[in]    l: float number
*/
extern void os_putf(float x,
                    uint8_t l);

__END_DECLS

__STATIC_INLINE
void usart_init(void)
{
    /* Enable the usart that connect to the upper computer */
    usart_dma_init(&huart_os);
    usart_dma_rx(&huart_os, os_buf + 1, BUFSIZ_OS - 1);
}

/* Enddef to prevent recursive inclusion */
#endif /* __BSP_USART_H__ */

/* END OF FILE */
