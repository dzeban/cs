#include <stdio.h>
#include <stdlib.h>

#include "queue_void.h"

struct queue *queue_init()
{
	struct queue *q;

	q = malloc(sizeof(*q));
	if (!q) return NULL;

	q->head = NULL;
	q->tail = NULL;
	return q;
}

void queue_free(struct queue *q)
{
	struct item *cur, *next;
	cur = q->head;

	while(cur)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}

	q->head = NULL;
	q->tail = NULL;
	free(q);
}

#if 0
/*
 * TODO: user should pass callback to print his item->p
 */
void queue_print(struct queue *q)
{
	struct item *cur;

	cur = q->head;
	while(cur)
	{
		printf("%d ", cur->n);
		cur = cur->next;
	}
	printf("\n");
}
#endif

int enq(struct queue *q, void *p)
{
	struct item *new;

	new = malloc(sizeof(*new));
	if (!new) return -1;
	
	new->p = p;
	new->next = NULL;

	// Enqueued first element
	if (q->head == NULL)
		q->head = new;

	// Add new to the tail
	if (q->tail)
		q->tail->next = new;

	// Shift tail
	q->tail = new;

	return 0;
}

int deq(struct queue *q, void **pp)
{
	struct item *head, *next;

	head = q->head;
	if (!head) return -1;

	next = head->next;

	*pp = head->p;
	q->head = next;
	free(head);

	// Dequeued last element
	if (q->head == NULL)
		q->tail = NULL;

	return 0;
}
