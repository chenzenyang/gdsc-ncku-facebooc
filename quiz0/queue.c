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

    if (!que) return NULL;

    que->head = NULL;
    que->tail = NULL;
    que->size = 0;
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
        free((q->head)->value);
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
    int s_len = strlen(s);

    if (!q) return false;

    element_t *elem = (element_t *) malloc(sizeof(element_t));
    if (!elem) return false;

    elem->value = (char *) malloc(sizeof(char) * (s_len + 1));
    if (!elem->value) {
        free(elem);
        return false;
    }

    strncpy(elem->value, s, s_len);
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
    int s_len = strlen(s);

    if (!q) return false;

    element_t *elem = (element_t *) malloc(sizeof(element_t));
    if (!elem) return false;

    elem->value = (char *) malloc(sizeof(char) * (s_len + 1));
    if (!elem->value) {
        free(elem);
        return false;
    }

    strncpy(elem->value, s, s_len);
    elem->next = NULL;

    (q->tail)->next = elem;
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
    if (dang) return false;

    element_t *tmp = q->head;
    free((q->head)->value);
    q->head = (q->head)->next;
    free(tmp);

    q->size--;
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
size_t q_size(queue_t *q)
{
    if (!q) return -1;
    
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
    if (!q) return;

    element_t *next, *perivous = NULL;
    q->tail = q->head;

    while (q) {
        next = (q->head)->next;
        (q->head)->next = perivous;
        perivous = q->head;
        q->head = next;
    }
}

/*
 * The function's sorting algorithm should be merge sort.
 */
void merge_sort(element_t **head)
{
    if (!(*head) || !(*head)->next)
        return;

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
