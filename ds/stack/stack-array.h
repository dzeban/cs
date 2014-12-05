#ifndef __STACK_ARRAY_H
#define __STACK_ARRAY_H

struct stack {
	int size;
	int top;
	int *array;
};

struct stack *stack_init(int size);
void stack_free(struct stack *stack);
void stack_print(struct stack *stack);
int stack_push(struct stack *stack, int elem);
int stack_pop(struct stack *stack);

#endif // __STACK_ARRAY_H
