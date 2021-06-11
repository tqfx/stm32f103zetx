/*!
 @file           bsp-flash.c
 @brief          bsp for flash
 @author         tqfx tqfx@foxmail.com
 @version        0
 @date           2021-06-11
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

#include "bsp-flash.h"

#include "main.h"

#include <string.h>

uint32_t flash_page(uint32_t addr)
{
    addr -= FLASH_BASE;
    addr /= FLASH_PAGE_SIZE;
    if (addr > FLASH_PAGE_TOTAL - 1)
    {
        addr = FLASH_PAGE_TOTAL - 1;
    }
    return addr;
}

uint32_t flash_page_next(uint32_t addr)
{
    addr += FLASH_PAGE_SIZE - addr % FLASH_PAGE_SIZE;
    if (addr > FLASH_PAGE_END - 1)
    {
        addr = FLASH_PAGE_END;
    }
    return addr;
}

int8_t flash_erase(uint32_t addr, uint32_t num)
{
    int8_t ret = 0;

    uint32_t error = 0;
    FLASH_EraseInitTypeDef erase = {0};
    erase.TypeErase = FLASH_TYPEERASE_PAGES;
    erase.PageAddress = addr;
    erase.NbPages = num;

    (void)HAL_FLASH_Unlock();
    if (HAL_FLASHEx_Erase(&erase, &error) != HAL_OK)
    {
        ret = -1;
    }
    (void)HAL_FLASH_Lock();

    return ret;
}

void flash_read(uint32_t addr,
                void *buf,
                uint32_t len)
{
    (void)memcpy(buf, (void *)addr, len);
}

int8_t flash_write(uint32_t addr,
                   void *buf,
                   uint32_t len)
{
    int8_t ret = 0;

    uint32_t *p = (uint32_t *)buf;
    uint32_t *d = p + (len >> 2) + (len % 4 ? 1 : 0);

    d = (uint32_t *)flash_page_next((uint32_t)d);

    /* Unlock the FLASH control register access */
    (void)HAL_FLASH_Unlock();

    while (p != d)
    {
        /* Program word word at a specified address */
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr, *p) != HAL_OK)
        {
            ret = -1;
            break;
        }
        addr += 4;
        ++p;
    }

    /* Locks the FLASH control register access */
    (void)HAL_FLASH_Lock();

    return ret;
}

int8_t flash_writen(uint32_t start,
                    uint32_t end,
                    void *buf,
                    uint32_t len)
{
    int8_t ret = 0;

    uint32_t *p = (uint32_t *)buf;
    uint32_t *d = p + (len >> 2) + (len % 4 ? 1 : 0);

    if (end < (uint32_t)d)
    {
        d = (uint32_t *)end;
    }

    /* Unlock the FLASH control register access */
    (void)HAL_FLASH_Unlock();

    while (p != d)
    {
        /* Program word word at a specified address */
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, start, *p) != HAL_OK)
        {
            ret = -1;
            break;
        }
        start += 4;
        ++p;
    }

    /* Locks the FLASH control register access */
    (void)HAL_FLASH_Lock();

    return ret;
}

/* END OF FILE */
