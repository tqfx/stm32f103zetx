/*!
 @file exec.h
 @brief Execution implementation.
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

/* Define to prevent recursive inclusion */
#ifndef __EXEC_H__
#define __EXEC_H__

#include "task.h"
#include <stdint.h>

#define KEY0_MSK (1 << 0)
#define KEY1_MSK (1 << 1)
#define KEYS_MSK (KEY1_MSK | KEY0_MSK)
#define PC_RXEN_MSK (1 << 0)
#define PC_RXBF_MSK (1 << 1)
typedef struct exec_s
{
  short exti;
  short uart;
  uint8_t *pc;
  float x;
  float y;
  float z;
  char c;
} exec_s;
extern exec_s exec[1];

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

void exec_init(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/* Enddef to prevent recursive inclusion */
#endif /* __EXEC_H__ */

/* END OF FILE */
