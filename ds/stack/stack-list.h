#ifndef __STACK_LIST_H
#define __STACK_LIST_H

struct stack {
	int n;
	struct stack *next;
};

struct stack *stack_init();
void stack_free(struct stack **stack);
int stack_push(struct stack **stack, int elem);
int stack_pop(struct stack **stack);
void stack_print(struct stack *stack);

#endif // __STACK_LIST_H
