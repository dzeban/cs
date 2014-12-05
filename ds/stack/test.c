#include <stdio.h>
#include <stdlib.h>

#include "stack-list.h"

#define N 10

int main(int argc, const char *argv[])
{
	struct stack *stack;

	stack = stack_init();

	stack_print(stack);

	stack_push(&stack, 1);
	stack_push(&stack, 2);
	stack_push(&stack, 3);
	stack_push(&stack, 4);
	stack_push(&stack, 5);
	stack_push(&stack, 6);

	stack_print(stack);

	printf("%d\n", stack_pop(&stack));
	printf("%d\n", stack_pop(&stack));
	printf("%d\n", stack_pop(&stack));
	printf("%d\n", stack_pop(&stack));

	stack_print(stack);

	stack_free(&stack);
	
	return 0;
}
