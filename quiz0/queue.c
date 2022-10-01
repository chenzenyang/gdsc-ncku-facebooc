#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *que = (queue_t *) malloc(sizeof(queue_t));

    if (que) {
        que->head = NULL;
        que->tail = NULL;
        que->size = 0;
    }
    return que;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (!q) return;

    element_t *tmp;
    while (q->head != NULL)
    {
        tmp = (q->head)->next;
        free((q->head)->value);     // 一開始沒注意到此
        free(q->head);
        q->head = tmp;
    }
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */

bool q_insert_head(queue_t *q, char *s)
{
    if (!q) return false;

    element_t *elem = (element_t *) malloc(sizeof(element_t));
    if (!elem) return false;

    elem->value = strdup(s);
    if (!elem->value) {
        free(elem);
        return false;
    }

    elem->next = q->head;

    q->head = elem;
    if (!q->tail) q->tail = elem;
    q->size++;

    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if (!q) return false;

    element_t *elem = (element_t *) malloc(sizeof(element_t));
    if (!elem) return false;

    elem->value = strdup(s);
    if (!elem->value) {
        free(elem);
        return false;
    }

    elem->next = NULL;

    if (q->tail) (q->tail)->next = elem;
    q->tail = elem;
    if (!q->head) q->head = elem;
    q->size++;

    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (!q || !q->head) return false;

    int *dang = memccpy(sp, (q->head)->value, '\0', bufsize - 1);
    if (!dang) return false;
    sp[(((char *) dang) - (q->head)->value)] = '\0';
    // sp[bufsize - 1] = '\0';

    element_t *temp = q->head;
    q->head = (q->head)->next;
    free(temp->value);
    free(temp);

    q->size--;
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
size_t q_size(queue_t *q)
{
    if (!q || !q->head) return -1;
    
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (!(q && q->head && (q->head)->next)) return;

    element_t *next = NULL, *perivous = NULL;
    q->tail = q->head;

    while (q->head) {
        next = (q->head)->next;
        (q->head)->next = perivous;
        perivous = q->head;
        q->head = next;
    }
    q->head = perivous;
}

void m_sorted(element_t **head, element_t *l_list, element_t *r_list)
{
    element_t *list = NULL;
    element_t **sorted = &list;

    for (element_t **lor = NULL; (l_list && r_list); *lor = (*lor)->next) {
        lor = ((strcmp(l_list->value, r_list->value) <= 0) ? &l_list : &r_list);
        *sorted = *lor;
        sorted = &(*sorted)->next;
    }

    *sorted = (l_list ? l_list : r_list);
    *head = list;
}


void cut_list(element_t *head, element_t **l_list, element_t **r_list)
{
    element_t *l_half = head;
    element_t *r_half = head->next;

    while (r_half && r_half->next) {
        l_half = l_half->next;
        r_half = r_half->next->next;
    }

    *l_list = head;
    *r_list = l_half->next;
    l_half->next = NULL;
}


/*
 * The function's sorting algorithm should be merge sort.
 */
void merge_sort(element_t **head)
{
    if (!(*head) || !(*head)->next)
        return;
    
    element_t *l_list = NULL;
    element_t *r_list = NULL;

    cut_list(*head, &l_list, &r_list);
    merge_sort(&r_list);
    merge_sort(&l_list);
    m_sorted(head, l_list, r_list);
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    if (!q || !q->head)
        return;

    merge_sort(&q->head);
    element_t *walk = q->head;
    while (walk->next)
        walk = walk->next;

    q->tail = walk;
}
