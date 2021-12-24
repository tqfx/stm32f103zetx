/*!
 @file pc.h
 @brief pc
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

/* Define to prevent recursive inclusion */
#ifndef __PC_H__
#define __PC_H__

#include "bsp.h"

#define hpc huart1 /* uart, connect to the upper computer */
#define PC_IRQHandler USART1_IRQHandler
extern UART_HandleTypeDef hpc;

#define PC_BUFSIZ 0x100
typedef union buf_u
{
  char s[PC_BUFSIZ];
  uint8_t u[PC_BUFSIZ];
  float f[PC_BUFSIZ >> 2];
} buf_u;

__BEGIN_DECLS

void pc_init(void);
void pc_printf(const char *format, ...);
void pc_justfloat(uint8_t n, ...);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __PC_H__ */

/* END OF FILE */
