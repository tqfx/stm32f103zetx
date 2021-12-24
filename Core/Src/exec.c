/*!
 @file exec.c
 @brief Execution implementation.
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "exec.h"
#include "main.h"
#include "bsp.h"

exec_s exec[1] = {{
  .exti = 0,
  .uart = 0,
  .c = 0,
  .x = 0,
  .y = 0,
  .z = 0,
}};

static task_s led[1];
static void exec_led(void *argv)
{
  (void)argv;
  gpio_pin_toggle(LEDR_GPIO_Port, LEDR_Pin);
}

static task_s key_led[1];
static void exec_led_on(void *argv)
{
  (void)argv;
  gpio_pin_reset(LEDG_GPIO_Port, LEDG_Pin);
}
static void exec_led_off(void *argv)
{
  (void)argv;
  gpio_pin_set(LEDG_GPIO_Port, LEDG_Pin);
}

static task_s key[1];
static void exec_key(void *argv)
{
  (void)argv;
  if (exec->exti & KEYS_MSK)
  {
    exec->exti &= ~KEYS_MSK;
    task_add(key_led);
    exec_led_on(argv);
  }
}

#include <stdlib.h>
static void exec_param(void *buf, uint16_t len)
{
#define IS_FLOAT(c) ((('0' <= c) && (c <= '9')) || (c == '.') || (c == '-'))
#define FLOAT_DEAL(x, p, q)         \
  {                                 \
    while (p != q && !IS_FLOAT(*p)) \
    {                               \
      ++p;                          \
    }                               \
    char *s = p;                    \
    while (p != q && IS_FLOAT(*p))  \
    {                               \
      ++p;                          \
    }                               \
    *p = 0;                         \
    x = atoff(s);                   \
  }
  char *p = (char *)buf;
  char *q = (char *)buf + len;
  if (*p++ == ':')
  {
    exec->c = *p++;
    if (exec->c)
    {
      FLOAT_DEAL(exec->x, p, q);
      FLOAT_DEAL(exec->y, p, q);
      FLOAT_DEAL(exec->z, p, q);
    }
    else
    {
      exec->x = 0;
      exec->y = 0;
      exec->z = 0;
    }
#undef FLOAT_DEAL
  }
#undef IS_FLOAT
}

#include "pc.h"
static task_s pc[1];
static void exec_pc(void *argv)
{
  (void)argv;
  if (exec->uart & PC_RXEN_MSK)
  {
    exec->uart &= ~PC_RXEN_MSK;
    exec_param(exec->pc + 1, *exec->pc);
    if (exec->c)
    {
      pc_printf(":%c %g %g %g\n", exec->c, exec->x, exec->y, exec->z);
    }
    switch (exec->c)
    {
    case 'l':
    {
      if (exec->x > 0)
      {
        gpio_pin_reset(LEDR_GPIO_Port, LEDR_Pin);
      }
      else if (exec->x < 0)
      {
        gpio_pin_set(LEDR_GPIO_Port, LEDR_Pin);
      }
      if (exec->y > 0)
      {
        gpio_pin_reset(LEDG_GPIO_Port, LEDG_Pin);
      }
      else if (exec->y < 0)
      {
        gpio_pin_set(LEDG_GPIO_Port, LEDG_Pin);
      }
    }
    break;
    default:
      break;
    }
  }
}

void exec_init(void)
{
  task_cron(led, exec_led, 0, 500);
  task_cron(key, exec_key, 0, 20);
  task_cron(pc, exec_pc, 0, 1);

  task_once(key_led, exec_led_off, 0, 100);

  task_add(led);
  task_add(key);
  task_add(pc);

  pc_init();
  pc_printf("OK\n");
}

/* END OF FILE */
