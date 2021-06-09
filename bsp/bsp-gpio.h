/*!
 @file           bsp-gpio.h
 @brief          bsp fo gpio
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
#ifndef __BSP_GPIO_H__
#define __BSP_GPIO_H__

#include "main.h"

#include <stdint.h>

__STATIC_INLINE
void gpio_pin_write(GPIO_TypeDef *gpio,
                    uint16_t pin,
                    FlagStatus state)
{
    if (state == SET)
    {
        gpio->BSRR = pin;
    }
    else
    {
        gpio->BSRR = (uint32_t)pin << 16U;
    }
}

__STATIC_INLINE
void gpio_pin_set(GPIO_TypeDef *gpio,
                  uint16_t pin)
{
    gpio->BSRR = pin;
}

__STATIC_INLINE
void gpio_pin_reset(GPIO_TypeDef *gpio,
                    uint16_t pin)
{
    gpio->BSRR = (uint32_t)pin << 16U;
}

__STATIC_INLINE
FlagStatus gpio_pin_read(GPIO_TypeDef *gpio,
                         uint16_t pin)
{
    if (gpio->IDR & pin)
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}

__STATIC_INLINE
void gpio_pin_toggle(GPIO_TypeDef *gpio,
                     uint16_t pin)
{
    if ((gpio->ODR & pin) == pin)
    {
        gpio->BSRR = (uint32_t)pin << 16U;
    }
    else
    {
        gpio->BSRR = pin;
    }
}

__STATIC_INLINE
void gpio_pin_lock(GPIO_TypeDef *gpio,
                   uint16_t pin)
{
    /* Apply lock key write sequence */
    __IO uint32_t tmp = GPIO_LCKR_LCKK | pin;
    /* Set LCKx bit(s): LCKK='1' + LCK[15-0] */
    gpio->LCKR = tmp;
    /* Reset LCKx bit(s): LCKK='0' + LCK[15-0] */
    gpio->LCKR = pin;
    /* Set LCKx bit(s): LCKK='1' + LCK[15-0] */
    gpio->LCKR = tmp;
    /* Read LCKR register. This read is mandatory to complete key lock sequence */
    tmp = gpio->LCKR;
}

/* Enddef to prevent recursive inclusion */
#endif /* __BSP_GPIO_H__ */

/* END OF FILE */
