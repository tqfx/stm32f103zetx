/*!
 @file           bsp-dma.h
 @brief          bsp fo dma
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
#ifndef __BSP_DMA_H__
#define __BSP_DMA_H__

#include "main.h"

/* Clear all flag */
#define BSP_DMA_CLEAR_FLAG(_)                                    \
    do                                                           \
    {                                                            \
        /* Clear Complete Transmit flag */                       \
        __HAL_DMA_CLEAR_FLAG(_, __HAL_DMA_GET_TC_FLAG_INDEX(_)); \
        /* Clear Half Complete Transmit flag */                  \
        __HAL_DMA_CLEAR_FLAG(_, __HAL_DMA_GET_HT_FLAG_INDEX(_)); \
        /* Clear Transfer error flag */                          \
        __HAL_DMA_CLEAR_FLAG(_, __HAL_DMA_GET_TE_FLAG_INDEX(_)); \
    } while (0)

/* Clear Complete Transmit flag */
#define BSP_DMA_CLEAR_TC(_) \
    __HAL_DMA_CLEAR_FLAG(_, __HAL_DMA_GET_TC_FLAG_INDEX(_))

/* Clear Half Complete Transmit flag */
#define BSP_DMA_CLEAR_HT(_) \
    __HAL_DMA_CLEAR_FLAG(_, __HAL_DMA_GET_HT_FLAG_INDEX(_))

/* Clear Transfer error flag */
#define BSP_DMA_CLEAR_TE(_) \
    __HAL_DMA_CLEAR_FLAG(_, __HAL_DMA_GET_TE_FLAG_INDEX(_))

/* Get Complete Transmit flag */
#define BSP_DMA_FLAG_TC(_) \
    __HAL_DMA_GET_FLAG(_, __HAL_DMA_GET_TC_FLAG_INDEX(_))

/* Get Half Complete Transmit flag */
#define BSP_DMA_FLAG_HT(_) \
    __HAL_DMA_GET_FLAG(_, __HAL_DMA_GET_HT_FLAG_INDEX(_))

/* Get Transfer error flag */
#define BSP_DMA_FLAG_TE(_) \
    __HAL_DMA_GET_FLAG(_, __HAL_DMA_GET_TE_FLAG_INDEX(_))

/* Wait Complete Transmit flag to be set */
#define BSP_DMA_WAIT_TC(_) \
    while (!__HAL_DMA_GET_FLAG(_, __HAL_DMA_GET_TC_FLAG_INDEX(_)))

/* Enddef to prevent recursive inclusion */
#endif /* __BSP_DMA_H__ */

/* END OF FILE */
