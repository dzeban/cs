#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "stack-list.h"

struct stack *stack_init()
{
	// We don't need any initialization
	return NULL;
}

void stack_free(struct stack **stack)
{
	struct stack *del = NULL;

	while (*stack)
	{
		del = *stack;
		*stack = (*stack)->next;
		free(del);
	}
}

int stack_push(struct stack **stack, int elem)
{
	struct stack *new = NULL;

	new = malloc(sizeof(*new));
	if (!new)
		return -1;

	new->n = elem;
	new->next = *stack;
	*stack = new;
	return 0;
}

int stack_pop(struct stack **stack)
{
	int val;
	struct stack *del;

	if (*stack == NULL)
		return INT_MAX;

	val = (*stack)->n;
	del = *stack;
	*stack = (*stack)->next;
	free(del);

	return val;
}

void stack_print(struct stack *stack)
{
	if (stack == NULL) {
		printf("Stack is empty.\n");
		return;
	}

	while(stack)
	{
		printf("%d ", stack->n);
		stack = stack->next;
	}

	printf("\n");
}
