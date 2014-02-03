#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define N 10

struct list *list_reverse(struct list *head)
{
    struct list *rev_head = NULL;
    struct list *rev_cur = NULL;
    struct list *cur = head;

    do 
    {
        rev_cur = (struct list *) malloc( sizeof(struct list) );
        rev_cur->n = cur->n;
        rev_cur->next = rev_head;
        rev_head = rev_cur;

    } while( cur = cur->next );

    return rev_head;
}

void list_reverse_inplace(struct list **head)
{
    struct list *rev;
    struct list *cur;
    struct list *tmp;
    
    cur = *head;
    rev = NULL;
    while( cur )
    {
        tmp = cur->next;
        cur->next = rev;
        rev = cur;
        cur = tmp;
    }

    *head = rev;
}

int main(int argc, const char *argv[])
{
    struct list *head, *rev, *rev2;

    head = list_constructor_tail(N);
    printf("Original list\n");
    list_print(head);
    printf("-----------------------------\n");

    rev = list_reverse(head);
    printf("Reverted list\n");
    list_print(rev);
    list_print(head);
    printf("-----------------------------\n");

    list_reverse_inplace(&head);
    printf("Inplace Reverted list\n");
    list_print(head);

    return 0;
}
