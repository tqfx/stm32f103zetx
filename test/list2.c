/*!
 @file list2.c
 @brief Circular doubly linked list tesing.
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "list2.h"

#include <stdlib.h>
#include <stdio.h>

#pragma pack(push, 4)
typedef struct list_int_s
{
    list2_s list[1];
    int data;
} list_int_s;
#pragma pack(pop)

static size_t list2_len(const list2_s *list)
{
    size_t count = 0;
    const list2_s *p;
    if (list)
    {
        if (list != list->tail)
        {
            list2_for_tail(p, list)
            {
                ++count;
            }
        }
        else if (list != list->head)
        {
            list2_for_head(p, list)
            {
                ++count;
            }
        }
    }
    return count;
}

static void test_tail(void)
{
    list2_s *list = (list2_s *)malloc(sizeof(list2_s));
    list2_ctor(list);
    for (int i = 0; i != 10; ++i)
    {
        list_int_s *node = (list_int_s *)malloc(sizeof(list_int_s));
        node->data = i;
        list2_add_tail(list, node->list);
    }
    list2_rot_tail(list);
    list2_s *list2 = (list2_s *)malloc(sizeof(list2_s));
    list2_ctor(list2);
    for (int i = 10; i != 20; ++i)
    {
        list_int_s *node = (list_int_s *)malloc(sizeof(list_int_s));
        node->data = i;
        list2_add_tail(list2, node->list);
    }
    list2_s *p;
    list2_mov_tail(list, list2);
    list2_for_tail(p, list)
    {
        list_int_s *node = list2_entry(p, list_int_s, list);
        printf("%i ", node->data);
    }
    printf("%zu", list2_len(list));
    list2_s *n;
    list2_forsafe_tail(p, n, list)
    {
        list_int_s *node = list2_entry(p, list_int_s, list);
        list2_del_node(node->list);
        free(node);
    }
    if (list2_empty(list) && list2_empty(list2))
    {
        printf(" ok\n");
    }
    free(list);
    free(list2);
}

static void test_head(void)
{
    list2_s *list = (list2_s *)malloc(sizeof(list2_s));
    list2_ctor(list);
    for (int i = 0; i != 10; ++i)
    {
        list_int_s *node = (list_int_s *)malloc(sizeof(list_int_s));
        node->data = i;
        list2_add_head(list, node->list);
    }
    list2_rot_head(list);
    list2_s *list2 = (list2_s *)malloc(sizeof(list2_s));
    list2_ctor(list2);
    for (int i = 10; i != 20; ++i)
    {
        list_int_s *node = (list_int_s *)malloc(sizeof(list_int_s));
        node->data = i;
        list2_add_head(list2, node->list);
    }
    list2_s *p;
    list2_mov_head(list, list2);
    list2_for_head(p, list)
    {
        list_int_s *node = list2_entry(p, list_int_s, list);
        printf("%i ", node->data);
    }
    printf("%zu", list2_len(list));
    list2_s *n;
    list2_forsafe_head(p, n, list)
    {
        list_int_s *node = list2_entry(p, list_int_s, list);
        list2_del_node(node->list);
        free(node);
    }
    if (list2_empty(list) && list2_empty(list2))
    {
        printf(" ok\n");
    }
    free(list);
    free(list2);
}

static void test_func(void)
{
    list2_s *list1 = (list2_s *)malloc(sizeof(list2_s));
    list2_ctor(list1);
    for (int i = 0; i != 10; ++i)
    {
        list_int_s *node = (list_int_s *)malloc(sizeof(list_int_s));
        node->data = i;
        list2_add_tail(list1, node->list);
    }
    list2_s *list2 = (list2_s *)malloc(sizeof(list2_s));
    list2_ctor(list2);
    for (int i = 10; i != 20; ++i)
    {
        list_int_s *node = (list_int_s *)malloc(sizeof(list_int_s));
        node->data = i;
        list2_add_tail(list2, node->list);
    }
    list_int_s *tmp = (list_int_s *)malloc(sizeof(list_int_s));
    tmp->data = -1;
    list2_s *p = list2->head;
    list2_sub_node(list2->head, tmp->list);
    tmp = list2_entry(p, list_int_s, list);
    list2_swap_node(list2->head, list2->tail);
    list2_for_tail(p, list1)
    {
        list_int_s *node = list2_entry(p, list_int_s, list);
        printf("%i ", node->data);
    }
    list2_for_tail(p, list2)
    {
        list_int_s *node = list2_entry(p, list_int_s, list);
        printf("%i ", node->data);
    }
    printf("%zu", list2_len(list1) + list2_len(list2));
    list2_s *n;
    list2_forsafe_tail(p, n, list1)
    {
        list_int_s *node = list2_entry(p, list_int_s, list);
        list2_del_node(node->list);
        free(node);
    }
    list2_forsafe_tail(p, n, list2)
    {
        list_int_s *node = list2_entry(p, list_int_s, list);
        list2_del_node(node->list);
        free(node);
    }
    if (list2_empty(list1) && list2_empty(list2))
    {
        printf(" ok\n");
    }
    free(tmp);
    free(list1);
    free(list2);
}

static void test_null(void)
{
    LIST2_HEAD(list1);
    LIST2_HEAD(list2);
    size_t len = list2_len(list1) + list2_len(list2);

    list2_add_head(list1, list1);
    len = list2_len(list1) + list2_len(list2);
    if (len != 0)
    {
        printf("failure in %s %i %zu\n", __FILE__, __LINE__, len);
    }

    list2_add_tail(list1, list1);
    len = list2_len(list1) + list2_len(list2);
    if (len != 0)
    {
        printf("failure in %s %i %zu\n", __FILE__, __LINE__, len);
    }

    list2_add_head(list1, list2);
    len = list2_len(list1) + list2_len(list2);
    if (len != 2)
    {
        printf("failure in %s %i %zu\n", __FILE__, __LINE__, len);
    }

    list2_add_tail(list1, list2);
    len = list2_len(list1) + list2_len(list2);
    if (len != 2)
    {
        printf("failure in %s %i %zu\n", __FILE__, __LINE__, len);
    }

    list2_del_node(list1);
    list2_del_node(list1);
    list2_ctor(list1);
    len = list2_len(list1) + list2_len(list2);
    if (len != 0)
    {
        printf("failure in %s %i %zu\n", __FILE__, __LINE__, len);
    }

    list2_rot_head(list1);
    list2_rot_tail(list1);
    len = list2_len(list1) + list2_len(list2);
    if (len != 0)
    {
        printf("failure in %s %i %zu\n", __FILE__, __LINE__, len);
    }

    list2_link(list1, list2);
    list2_loop(list1, list2);
    len = list2_len(list1) + list2_len(list2);
    if (len != 2)
    {
        printf("failure in %s %i %zu\n", __FILE__, __LINE__, len);
    }

    list2_rot_head(list1);
    list2_rot_head(list1);
    list2_rot_tail(list1);
    len = list2_len(list1) + list2_len(list2);
    if (len != 2)
    {
        printf("failure in %s %i %zu\n", __FILE__, __LINE__, len);
    }

    list2_swap_node(list1, list1);
    list2_swap_node(list2, list2);
    len = list2_len(list1) + list2_len(list2);
    if (len != 2)
    {
        printf("failure in %s %i %zu\n", __FILE__, __LINE__, len);
    }

    list2_swap_node(list1, list2);
    len = list2_len(list1) + list2_len(list2);
    if (len != 0)
    {
        printf("failure in %s %i %zu\n", __FILE__, __LINE__, len);
    }

    list2_swap_node(list2, list1);
    len = list2_len(list1) + list2_len(list2);
    if (len != 2)
    {
        printf("failure in %s %i %zu\n", __FILE__, __LINE__, len);
    }

    list2_sub_node(list1, list1);
    list2_sub_node(list2, list2);
    len = list2_len(list1) + list2_len(list2);
    if (len != 2)
    {
        printf("failure in %s %i %zu\n", __FILE__, __LINE__, len);
    }

    list2_sub_node(list2, list1);
    list2_ctor(list2);
    len = list2_len(list1) + list2_len(list2);
    if (len != 0)
    {
        printf("failure in %s %i %zu\n", __FILE__, __LINE__, len);
    }
}

int main(void)
{
    test_tail();
    test_head();
    test_func();
    test_null();
    return 0;
}

/* END OF FILE */
