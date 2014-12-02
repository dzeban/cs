#include <stdio.h>  // printf
#include <stdbool.h>
#include "list.h"

struct list *get_kth(struct list *head, int k, int length)
{
	int len, counter;

	if (k == 0)
		return NULL;
	
	if (k > length)
		return NULL;

	counter = length - k;
	while (counter--)
		head = head->next;

	return head;
}

bool is_palindrome(struct list *head)
{
	struct list *front, *back;
	int len, k;

	len = list_length(head);

	if (len == 0)
		return false;
	if (len == 1)
		return true;
	
	front = head;
	k = 1;
	while(k <= len/2)
	{
		back = get_kth(head, k, len);
		if (!back)
			return false;

		if (front->n != back->n)
			return false;

		front = front->next;
		k++;
	}

	return true;
}

void reverse(struct list **head)
{
	struct list *cur, *prev, *tmp;

	cur = *head;
	prev = NULL;
	while (cur)
	{
		tmp = cur;
		cur = cur->next;
		tmp->next = prev;
		prev = tmp;
	}

	*head = prev;
}

void swap(struct list **pp1, struct list **pp2)
{
	struct list *tmp;

	// Swap next pointers
	tmp = (*pp1)->next;
	(*pp1)->next = (*pp2)->next;
	(*pp2)->next = tmp;

	// Swap previous pointers
	tmp = *pp1;
	*pp1 = *pp2;
	*pp2 = tmp;

}

int main(int argc, const char *argv[])
{
    struct list *head = NULL;
	struct list *p1 = NULL;
	struct list *p2 = NULL;
	int len;

	head = list_constructor_va(5, 5,4,3,2,1);
	/*head = list_constructor_head(9);*/
    list_print(head);

	len = list_length(head);
	p1 = get_kth(head, 4, len);
	p2 = get_kth(head, 2, len);

	swap(&p1, &p2);
	
	list_print(head);

    return 0;
}
