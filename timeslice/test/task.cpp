/*!
 @file task.cpp
 @brief Cooperative scheduler task tesing.
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include <thread>
#include <stdio.h>
#include <unistd.h>
#include "task.h"

static task_s task[6];

static void task1_exec(void *arg)
{
    size_t *p = (size_t *)arg;
    if (++*p % 2 == 0)
    {
        task_del(task + 1);
    }
}

static void task2_exec(void *arg)
{
    size_t *p = (size_t *)arg + 1;
    if (++*p % 2 == 0)
    {
        task_add(task + 1);
    }
}

static void task3_exec(void *arg)
{
    ++*((size_t *)arg + 2);
}

static void task4_exec(void *arg)
{
    ++*((size_t *)arg + 3);
}

static void task5_exec(void *arg)
{
    ++*((size_t *)arg + 4);
}

static size_t ref[5] = {0};
static void task_ctor(void)
{
    task_ctor(task + 1, task1_exec, ref, 10);
    task_ctor(task + 2, task2_exec, ref, 20);
    task_ctor(task + 3, task3_exec, ref, 30);
    task_ctor(task + 4, task4_exec, ref, 40);
    task_ctor(task + 5, task5_exec, ref, 50);
    task_add(task + 1);
    task_add(task + 2);
    task_add(task + 3);
    task_add(task + 4);
    task_add(task + 5);
}

static void task_exec_thread(void)
{
    while (true)
    {
        task_exec();
        usleep(1000);
    }
}

static void task_show(void *arg)
{
    printf("\r\n");
    printf("\rtask1 %zu\n", *((size_t *)arg + 0));
    printf("\rtask2 %zu\n", *((size_t *)arg + 1));
    printf("\rtask3 %zu\n", *((size_t *)arg + 2));
    printf("\rtask4 %zu\n", *((size_t *)arg + 3));
    printf("\rtask5 %zu\n", *((size_t *)arg + 4));
    printf("\r\033[6A");
}
static void task_tick_thread(void)
{
    static size_t n = 0;
    while (true)
    {
        task_tick();
        printf("\rcount %zu tick %zu", task_count(), ++n);
        task_show(ref);
        usleep(100000);
    }
}

int main(void)
{
    task_ctor();

    task_del(task + 2);
    if (task_exist(task + 2))
    {
        printf("failure in %s %i\n", __FILE__, __LINE__);
    }

    task_del(task + 5);
    if (task_count() != 3)
    {
        printf("failure in %s %i\n", __FILE__, __LINE__);
    }
    if (task_exist(task + 3) == 0)
    {
        printf("failure in %s %i\n", __FILE__, __LINE__);
    }
    task_add(task + 2);
    if (task_exist(task + 2) == 0)
    {
        printf("failure in %s %i\n", __FILE__, __LINE__);
    }
    task_add(task + 5);

    std::thread thread_1(task_exec_thread);
    std::thread thread_2(task_tick_thread);

    thread_1.join();
    thread_2.join();

    return 0;
}

/* END OF FILE */
