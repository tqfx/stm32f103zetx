/*!
 @file exec.c
 @brief Execution implementation.
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "exec.h"
#include "main.h"

static void exec_toggle_led(void *arg)
{
  size_t id = (size_t)arg;
  switch (id)
  {
  case 0:
  {
    HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
  }
  break;
  case 1:
  {
    HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
  }
  break;
  default:
    break;
  }
}

void exec_init(void)
{
  static task_s led0;
  task_ctor(&led0, exec_toggle_led, (void *)0, 500);
  task_add(&led0);
  static task_s led1;
  task_ctor(&led1, exec_toggle_led, (void *)1, 1000);
  task_add(&led1);
}

/* END OF FILE */
