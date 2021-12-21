/*!
 @file task.c
 @brief task implementation.
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "task.h"

static LIST2_HEAD(task_list);

void task_exec(void)
{
    task_s *task;
    list2_s *node, *next;
    list2_forsafe_tail(node, next, task_list)
    {
        task = list2_entry(node, task_s, list);
        if (task->state == TASK_EXEC)
        {
            task->exec(task->arg);
            task->state = TASK_WAIT;
        }
    }
}

void task_tick(void)
{
    task_s *task;
    list2_s *node, *next;
    list2_forsafe_tail(node, next, task_list)
    {
        task = list2_entry(node, task_s, list);
        if (task->timer)
        {
            if (--task->timer == 0)
            {
                task->state = TASK_EXEC;
                task->timer = task->slice;
            }
        }
    }
}

void task_ctor(task_s *ctx, void (*exec)(void *), void *arg, size_t slice)
{
    ctx->timer = ctx->slice = slice;
    ctx->state = TASK_WAIT;
    list2_ctor(ctx->list);
    ctx->exec = exec;
    ctx->arg = arg;
}

void task_add(task_s *ctx)
{
    list2_del_node(ctx->list);
    list2_add_tail(task_list, ctx->list);
}

void task_del(task_s *ctx)
{
    list2_del_node(ctx->list);
}

int task_exist(task_s *ctx)
{
    task_s *task;
    list2_s *node;
    list2_for_tail(node, task_list)
    {
        task = list2_entry(node, task_s, list);
        if (ctx->list == task->list)
        {
            return 1;
        }
    }
    return 0;
}

size_t task_slice(task_s *ctx)
{
    return ctx->slice;
}

size_t task_count(void)
{
    return list2_len(task_list);
}

/* END OF FILE */
