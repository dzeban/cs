/* 
 * File sorted.c
 *
 * Implements sorted linked list with add/remove functions
 *
 */

#include <stdlib.h> // malloc
#include <stdio.h> // printf
#include "list.h"

void sorted_add(struct list **head, int n)
{
    struct list *new = NULL;
    struct list **cur = head;

    new = malloc(sizeof(*new));
    new->n = n;
    
    while( *cur )
    {
        if((*cur)->n >= n)
        {
            break;
        }

        cur = &((*cur)->next);
    }

    new->next = *cur;
    *cur = new;
}

int main(int argc, const char *argv[])
{
    struct list *head;

    printf("Original list:\n");
    head = list_constructor_tail(10);
    list_print(head);

    printf("Adding -1:\n");
    sorted_add(&head, -1);
    list_print(head);

    printf("Adding 4:\n");
    sorted_add(&head, 4);
    list_print(head);

    printf("Adding 12:\n");
    sorted_add(&head, 12);
    list_print(head);

    printf("Adding 10:\n");
    sorted_add(&head, 10);
    list_print(head);
    return 0;
}
