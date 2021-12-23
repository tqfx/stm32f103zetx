/*!
 @file task.c
 @brief task implementation.
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "task.h"

static LIST2_HEAD(task_list);
static size_t task_counter = 0;
static task_s *task_current = 0;

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
                task->state |= TASK_EXEC;
                task->timer = task->slice;
            }
        }
    }
}

void task_exec(void)
{
    list2_s *node, *next;
    list2_forsafe_tail(node, next, task_list)
    {
        task_current = list2_entry(node, task_s, list);
        if (task_current->state & TASK_EXEC)
        {
            task_current->exec(task_current->argv);
            task_current->state &= ~TASK_EXEC;
            if (task_current->state & TASK_ONCE)
            {
                task_del(task_current);
            }
        }
    }
}

void task_cron(task_s *ctx, void (*exec)(void *), void *argv, size_t slice)
{
    ctx->timer = ctx->slice = slice;
    ctx->state = TASK_CRON;
    list2_ctor(ctx->list);
    ctx->exec = exec;
    ctx->argv = argv;
}

void task_once(task_s *ctx, void (*exec)(void *), void *argv, size_t delay)
{
    ctx->timer = ctx->slice = delay;
    ctx->state = TASK_ONCE;
    list2_ctor(ctx->list);
    ctx->exec = exec;
    ctx->argv = argv;
}

void task_set_exec(task_s *ctx, void (*exec)(void *))
{
    task_s *task = ctx ? ctx : task_current;
    task->exec = exec;
}
void task_set_argv(task_s *ctx, void *argv)
{
    task_s *task = ctx ? ctx : task_current;
    task->argv = argv;
}
void task_set_timer(task_s *ctx, size_t timer)
{
    task_s *task = ctx ? ctx : task_current;
    task->timer = timer;
}
void task_set_slice(task_s *ctx, size_t slice)
{
    task_s *task = ctx ? ctx : task_current;
    task->slice = slice;
}

void task_add(task_s *ctx)
{
    task_s *task = ctx ? ctx : task_current;
    if ((task->state & TASK_CTRL) == TASK_NULL)
    {
        list2_add_tail(task_list, task->list);
        task->state |= TASK_LOAD;
        ++task_counter;
    }
}

void task_del(task_s *ctx)
{
    task_s *task = ctx ? ctx : task_current;
    if ((task->state & TASK_CTRL) != TASK_NULL)
    {
        list2_del_node(task->list);
        task->state &= ~TASK_CTRL;
        --task_counter;
    }
}

int task_exist(task_s *ctx)
{
    task_s *task = ctx ? ctx : task_current;
#if 1
    if (task->state & TASK_LOAD)
    {
        return 1;
    }
#else
    list2_s *node;
    list2_for_tail(node, task_list)
    {
        task = list2_entry(node, task_s, list);
        if (ctx->list == task->list)
        {
            return 1;
        }
    }
#endif
    return 0;
}

size_t task_timer(task_s *ctx)
{
    task_s *task = ctx ? ctx : task_current;
    return task->timer;
}
size_t task_slice(task_s *ctx)
{
    task_s *task = ctx ? ctx : task_current;
    return task->slice;
}

size_t task_count(void)
{
#if 1
    return task_counter;
#else
    size_t count = 0;

    list2_s *node;
    if (task_list != task_list->tail)
    {
        list2_for_tail(node, task_list)
        {
            ++count;
        }
    }

    return count;
#endif
}

/* END OF FILE */
