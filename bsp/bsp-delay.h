/*!
 @file           bsp-delay.h
 @brief          bsp fo delay
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
#ifndef __BSP_DELAY_H__
#define __BSP_DELAY_H__

#include "bsp.h"

#include <stdint.h>

__BEGIN_DECLS

/*!
 @brief          Delay microseconds
 @param[in]      nus: 0x0000 ~ 0xFFFF
*/
extern void delay_us(uint16_t nus);

/*!
 @brief          Delay millisecond
 @param[in]      nms: 0x0000 ~ 0xFFFF
*/
extern void delay_ms(uint16_t nms);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __BSP_DELAY_H__ */

/* END OF FILE */
