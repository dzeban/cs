#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

// Double pointer is used to modify *original* pointer to list head - not a copy
// See <http://c-faq.com/ptrs/passptrinit.html>
void list_add_head(int i, struct list **head)
{
    struct list *item = (struct list *)malloc(sizeof(struct list));

    item->n = i;
    item->next = *head;
    *head = item;

    return;
}

// We do NOT need double pointer on head here because head is not modified - we
// are adding to tail.
void list_add_tail(int i, struct list *head)
{
    struct list *item = (struct list *)malloc(sizeof(struct list));
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
        if( cur->n == i )
        {
            if( prev )
            {
                prev->next = cur->next;
            }
            else
            {
                *head = cur->next;
            }
            free(cur);
        }

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
    while((*pp)->next)
    {
        cur = *pp;
        if(cur->n == i)
        {
            *pp = cur->next;
            free(cur);
        }

        pp = &(cur->next);   
    }
}

struct list *list_constructor_head(int n)
{
    struct list *head = NULL;
    struct list *cur = NULL;
    int i = 0;

    for( i = 0; i < n; i++ )
    {
        cur = (struct list *) malloc( sizeof(struct list) );
        if( !cur ) 
            return NULL;

        cur->n = i;
        cur->next = head;
        head = cur;
    }

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
        cur = (struct list *) malloc( sizeof(struct list) );
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
    printf("%p( %d ) -> NULL\n", cur, cur->n);
    return;
}
