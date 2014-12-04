#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "list.h"

// Double pointer is used to modify *original* pointer to list head - not a copy
// See <http://c-faq.com/ptrs/passptrinit.html>
void list_push(int i, struct list **head)
{
    // sizeof(*item) is better then sizeof(struct list) because if I change type
    // of item malloc will still be working.

    struct list *item = malloc(sizeof(*item));

    item->n = i;
    item->next = *head;
    *head = item;

    return;
}

// We do NOT need double pointer on head here because head pointer is not
// modified - we are adding to tail.
void list_append(int i, struct list *head)
{
    struct list *item = malloc(sizeof(*item));
    item->n = i;
    item->next = NULL;

    while(head->next)
    {
        head = head->next;
    }

    head->next = item;
}

// Actualy, returns sublist starting from search key
struct list *list_search(int n, struct list *head)
{
    while(head->next) 
    {
        if (head->n == n)
        {
            // Found!
            return head;
        }
        head = head->next;
    }

    // Not found
    return NULL;
}

void list_remove(int i, struct list **head)
{
    struct list *cur = *head;
    struct list *prev = NULL;
    while(cur->next)
    {
        if( cur->n == i ) // Found element to remove
        {
            if( prev )
            {
                // Make previous pointer around deleted element
                prev->next = cur->next;
            }
            else
            {
                // prev == NULL means we removing head, 
                // so shift head to next element.
                *head = cur->next;
            }
            free(cur);
        }

        // Iterating...
        prev = cur;
        cur = cur->next;
    }
}

// As seen in <http://www.eskimo.com/~scs/cclass/int/sx8.html>
// And in <http://wordaligned.org/articles/two-star-programming>
void list_remove_pp(int i, struct list **head)
{
    struct list **pp;
    struct list *cur;

    pp = head;
    while(*pp)
    {
        cur = *pp;
        if(cur->n == i)
        {
            *pp = cur->next;
            free(cur);
        }
        pp = &((*pp)->next);   
    }
}

struct list *list_constructor_head(int n)
{
    struct list *head = NULL;
    int i = 0;

    for( i = 0; i < n; i++ )
    {
        list_push(i, &head);
    }

    return head;
}

struct list *list_constructor_va(int count, ...)
{
	struct list *head = NULL;
	int i, n;
	va_list ap;

	va_start (ap, count);
	for (i = 0; i < count; i++)
	{
		n = va_arg(ap, int);
		list_push(n, &head);
	}
	va_end (ap);

	return head;
}

struct list *list_constructor_tail(int n)
{
    struct list *head = NULL;
    struct list *tail = NULL;
    struct list *cur = NULL;
    int i = 0;

    for( i = 0; i < n; i++ )
    {
        cur = (struct list *) malloc( sizeof(*cur) );
        cur->n = i;
        cur->next = NULL;

        if( !head ) head = cur;
        if( !tail ) 
        {
            tail = cur;
            continue;
        }

        tail->next = cur;
        tail = cur;
    }

    return head;
}

struct list *list_constructor_dup(int n, int d)
{
    struct list *head = NULL;
    int i, j;

    for( i = 0; i < n; i++ )
    {
        for( j = 0; j < d; j++ )
        {
            list_push( i, &head );
        }
    }

    return head;
}

void list_print(struct list *head)
{
    struct list *cur = head;

    if( !head )
    {
        printf("List head is null. Can't print\n");
        return;
    }

    while( cur->next )
    {
        printf("%p( %d ) -> ", cur, cur->n);
        cur = cur->next;
    }
    printf("%p( %d ) -> NULL\n\n", cur, cur->n);
    return;
}

int list_length(struct list *head)
{
    int length = 0;

    while(head)
    {
        length++;
        head = head->next;
    }

    return length;
}
