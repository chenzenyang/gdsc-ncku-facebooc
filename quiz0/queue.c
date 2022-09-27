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
    queue_t *que_n = (queue_t *) malloc(sizeof(queue_t));

    if (!que_n) {
        que_n->head = NULL;
        que_n->tail = NULL;
        que_n->size = 0;
        return que_n;
    }
    return NULL;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (!q) return;

    element_t *tmp;
    while (q->head != NULL)
    {
        tmp = q->head;
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

    elem->value = malloc(sizeof(char) * (strlen(s) + 1));
    if (!elem->value) {
        free(elem);
        return false;
    }
    strcpy(elem->value, s);
    elem->next = q->head;

    q->head = elem;
    if (!elem->next) q->tail = elem;
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
    
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
size_t q_size(queue_t *q)
{
    return -1;
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
