#include <stdlib.h>

#include "list.h"

static void remove(struct list **node)
{
	struct list *del;

	del = *node;
	*node = (*node)->next;
	free(del);
}

void dedup(struct list *head)
{
	struct list *cur, **pp;
	struct list *del;
	
	cur = head;
	while (cur)
	{
		pp = &(cur->next);
		while (*pp)
		{
			if (cur->n == (*pp)->n)
			{
				del = *pp;
				*pp = (*pp)->next;
				free(del);
			}
			else
			{
				pp = &((*pp)->next);
			}
			list_print(head);
		}
		cur = cur->next;
	}
}

