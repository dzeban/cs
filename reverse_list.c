#include <stdio.h>
#include <stdlib.h>

#define N 10

struct list {
    int n;
    struct list *next;
};

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

struct list *list_reverse_inplace(struct list *head)
{
    struct list *new = NULL;
    struct list *cur = NULL;
    
    while(head)
    {
        cur = head;
        cur->next = new;
        new = cur;
        head = head->next;
    }

    return new;
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

    rev2 = list_reverse_inplace(head);
    printf("Inplace Reverted list\n");
    list_print(rev);
    list_print(head);

    return 0;
}
