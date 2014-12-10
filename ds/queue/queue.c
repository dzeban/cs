#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

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

int enq(struct queue *q, int n)
{
	struct item *new;

	new = malloc(sizeof(*new));
	if (!new) return -1;
	
	new->n = n;
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

int deq(struct queue *q, int *n)
{
	struct item *head, *next;

	head = q->head;
	if (!head) return -1;

	next = head->next;

	*n = head->n;
	q->head = next;
	free(head);

	// Dequeued last element
	if (q->head == NULL)
		q->tail = NULL;

	return 0;
}
