#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "stack-array.h"

struct stack *
stack_init(int size)
{
	struct stack *stack = NULL;

	if (size < 1) {
		return NULL;
	}

	stack = malloc(sizeof(*stack));
	if (!stack) {
		goto err;
	}

	stack->array = calloc(size, sizeof(int));
	if (!stack->array) {
		goto err;
	}

	stack->top = -1;
	stack->size = size;
	return stack;

err:
	stack_free(stack);
	return NULL;
}

void 
stack_free(struct stack *stack)
{
	if (stack->array) {
		free(stack->array);
	}

	if (stack) {
		free(stack);
	}
}

void 
stack_print(struct stack *stack)
{
	int i;
	if (stack->top < 0) {
		printf("Stack is empty\n");
		return;
	}

	for (i = 0; i <= stack->top; i++) {
		printf("%d ", stack->array[i]);
	}

	printf("\n");
}

int
stack_push(struct stack *stack, int elem)
{
	if (stack->top == stack->size - 1) {
		fprintf(stderr, "Stack if full\n");
		return -1;
	}

	stack->top++;
	stack->array[stack->top] = elem;
	return 0;
}

int
stack_pop(struct stack *stack)
{
	if (stack->top < 0) {
		fprintf(stderr, "Stack is empty\n");
		return INT_MAX;
	}

	return stack->array[stack->top--];
}
