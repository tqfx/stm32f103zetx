/*!
 @file task.h
 @brief Cooperative scheduler task implementation.
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

/* Define to prevent recursive inclusion */
#ifndef __TASK_H__
#define __TASK_H__

#include "list2.h"

typedef enum task_e
{
    TASK_NULL = 0,
    TASK_CTRL = 0x00FF,
    TASK_LOAD = 1 << 0,
    TASK_EXEC = 1 << 7,
} task_e;

#ifndef _MSC_VER
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* _MSC_VER */

typedef struct task_s
{
    list2_s list[1];
    void (*exec)(void *);
    size_t slice;
    size_t timer;
    void *argv;
    int state;
} task_s;

#ifndef _MSC_VER
#pragma GCC diagnostic pop
#endif /* _MSC_VER */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

void task_tick(void);
void task_exec(void);
void task_cron(task_s *ctx, void (*exec)(void *), void *argv, size_t slice);
void task_once(task_s *ctx, void (*exec)(void *), void *argv, size_t timer);
void task_set_exec(task_s *ctx, void (*exec)(void *));
void task_set_argv(task_s *ctx, void *argv);
void task_set_timer(task_s *ctx, size_t timer);
void task_set_slice(task_s *ctx, size_t slice);
void task_add(task_s *ctx);
void task_del(task_s *ctx);
int task_exist(task_s *ctx);
size_t task_timer(task_s *ctx);
size_t task_slice(task_s *ctx);
size_t task_count(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/* Enddef to prevent recursive inclusion */
#endif /* __TASK_H__ */

/* END OF FILE */
