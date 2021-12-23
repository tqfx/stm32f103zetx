/*!
 @file list2.h
 @brief Circular doubly linked list implementation.
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

/* Define to prevent recursive inclusion */
#ifndef __LIST2_H__
#define __LIST2_H__

#include <stddef.h>

#ifndef offsetof
#define offsetof(type, member) (size_t)(&(((type *)0)->member))
#endif /* offsetof */
#ifndef containerof
#define containerof(ptr, type, member) ((type *)((size_t)(ptr)-offsetof(type, member)))
#endif /* containerof */
#define inline __inline

typedef struct list2_s
{
    struct list2_s *head, *tail;
} list2_s;

#define LIST2_HEAD_INIT(name) \
    {                         \
        &(name), &(name)      \
    }
#define LIST2_HEAD(name) list2_s name[1] = {{name, name}}

#define list2_entry(ptr, type, member)      containerof(ptr, type, member)
#define list2_entry_head(ptr, type, member) list2_entry((ptr)->head, type, member)
#define list2_entry_tail(ptr, type, member) list2_entry((ptr)->tail, type, member)

#define list2_for_(p, list, next) \
    for ((p) = (list)->next; (p) != (list); (p) = (p)->next)
#define list2_for_head(p, list) list2_for_(p, list, head)
#define list2_for_tail(p, list) list2_for_(p, list, tail)

#define list2_forsafe_(p, n, list, next) \
    for ((p) = (list)->next, (n) = (p)->next; (p) != (list); (p) = (n), (n) = (p)->next)
#define list2_forsafe_head(p, n, list) list2_forsafe_(p, n, list, head)
#define list2_forsafe_tail(p, n, list) list2_forsafe_(p, n, list, tail)

static inline void list2_ctor(list2_s *list)
{
    list->head = list->tail = list;
}
static inline void list2_link(list2_s *head, list2_s *tail)
{
    head->tail = tail;
    tail->head = head;
}
static inline void list2_loop(list2_s *head, list2_s *tail)
{
    head->head = tail;
    tail->tail = head;
}

static inline void list2_add_(list2_s *head1, list2_s *tail1,
                              list2_s *head2, list2_s *tail2)
{
    list2_link(tail1, head2);
    list2_link(tail2, head1);
}
static inline void list2_add_node(list2_s *head, list2_s *tail, list2_s *node)
{
    list2_add_(head, tail, node, node);
}
static inline void list2_add_head(list2_s *list, list2_s *node)
{
    list2_add_node(list->tail, list, node);
}
static inline void list2_add_tail(list2_s *list, list2_s *node)
{
    list2_add_node(list, list->head, node);
}
static inline void list2_mov_head(list2_s *list1, list2_s *list2)
{
    list2_add_(list1->tail, list1, list2->tail, list2->head);
    list2_loop(list2, list2);
}
static inline void list2_mov_tail(list2_s *list1, list2_s *list2)
{
    list2_add_(list1, list1->head, list2->tail, list2->head);
    list2_loop(list2, list2);
}

static inline void list2_del_(list2_s *head, list2_s *tail)
{
    list2_link(head->head, tail->tail);
}
static inline void list2_del_node(list2_s *node)
{
    list2_del_(node, node);
}
static inline void list2_rot_head(list2_s *list)
{
    list2_s *node = list->tail;
    list2_del_(node, node);
    list2_add_tail(list, node);
}
static inline void list2_rot_tail(list2_s *list)
{
    list2_s *node = list->head;
    list2_del_(node, node);
    list2_add_head(list, node);
}

static inline void list2_sub_(list2_s *head1, list2_s *tail1,
                              list2_s *head2, list2_s *tail2)
{
    list2_add_(tail1->tail, head1->head, head2, tail2);
}
static inline void list2_sub_node(list2_s *lold, list2_s *lnew)
{
    if (lold != lnew)
    {
        list2_sub_(lold, lold, lnew, lnew);
    }
}

static inline void list2_swap_(list2_s *head1, list2_s *tail1,
                               list2_s *head2, list2_s *tail2)
{
    list2_s *head = tail2->tail, *tail = head2->head;
    list2_add_(tail1->tail, head1->head, head2, tail2);
    list2_add_(head, tail, head1, tail1);
}
static inline void list2_swap_node(list2_s *node1, list2_s *node2)
{
    list2_swap_(node1, node1, node2, node2);
}

static inline int list2_empty(const list2_s *list)
{
    return list && (list == list->head) && (list == list->tail);
}

/* Enddef to prevent recursive inclusion */
#endif /* __LIST2_H__ */

/* END OF FILE */
