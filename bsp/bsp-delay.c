/*!
 @file           bsp-delay.c
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

#include "bsp-delay.h"

#include "main.h"

void delay_us(uint16_t nus)
{
    uint32_t tcnt = 0U;
    uint32_t tnow = 0U;
    uint32_t ticks = nus * (SystemCoreClock / 1000000U);
    uint32_t reload = SysTick->LOAD; /* SysTick Reload Value Register */
    uint32_t told = SysTick->VAL;    /* SysTick Current Value Register */
    do
    {
        tnow = SysTick->VAL;
        if (tnow == told)
        {
            continue;
        }
        if (tnow < told)
        {
            tcnt += told - tnow;
        }
        else
        {
            tcnt += reload + told - tnow;
        }
        told = tnow;
    } while (tcnt < ticks);
}

void delay_ms(uint16_t nms)
{
    uint32_t tcnt = 0U;
    uint32_t tnow = 0U;
    uint32_t ticks = nms * (SystemCoreClock / 1000U);
    uint32_t reload = SysTick->LOAD; /* SysTick Reload Value Register */
    uint32_t told = SysTick->VAL;    /* SysTick Current Value Register */
    do
    {
        tnow = SysTick->VAL;
        if (tnow == told)
        {
            continue;
        }
        if (tnow < told)
        {
            tcnt += told - tnow;
        }
        else
        {
            tcnt += reload + told - tnow;
        }
        told = tnow;
    } while (tcnt < ticks);
}

/* END OF FILE */
