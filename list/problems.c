#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

// Problem 1.
//
// Write a Count() function that counts the number of times a given int occurs
// in a list.
int count(int n, struct list *head)
{
    int count = 0;
    while( head )
    {
        if( head->n == n )
            count++;

        head = head->next;
    }

    return count;
}

// Problem 2.
//
// Write a function that takes a linked list and an integer index and returns
// the data value stored in the node at that index position. 
//
// So for the list {42, 13, 666} GetNth() with index 1 should return 13.  The
// index should be in the range [0..length-1]. If it is not, it should assert()
// fail.
int get(int n, struct list *head)
{
    int i = 0;
    while( head )
    {
        if( i == n )
            return head->n;

        head = head->next;
        i++;
    }

    assert(n > i);
}

// Problem 3.
//
// Write a function that takes a list, deallocates all of its memory and sets
// its head pointer to NULL (the empty list).
void delete(struct list **head)
{
    struct list *cur = *head;
    struct list *tmp;

    while(cur)
    {
        tmp = cur;
        cur = cur->next;        
        free(tmp);
    }

    *head = NULL;
}

// Problem 4.
//
// Write a Pop() function that is the inverse of Push(). Pop() takes a non-empty
// list, deletes the head node, and returns the head node's data. Pop() should
// assert() fail if there is not a node to pop.
int pop(struct list **head)
{
    struct list *cur = *head;
    int val;

    val = cur->n;
    *head = (*head)->next;
    free(cur);

    return val;
}

// Problem 5.
//
// Write a function which can insert a new node at any index within a list.  The
// caller may specify any index in the range [0..length], and the new node
// should be inserted so as to be at that index. 
void insert(struct list **head, int index, int n)
{
    struct list **pp;
    struct list *new;
    int i;

    pp = head;
    while(*pp)
    {
        if( i == index )
        {
            new = malloc(sizeof(*new));
            new->n = n;
            new->next = *pp;
            *pp = new;
            break;
        }

        pp = &((*pp)->next);
        i++;
    }
}

// Problem 6.
//
// Write a function which given a list that is sorted in increasing order, and a
// single node, inserts the node into the correct sorted position in the list.
void insert_sorted(struct list **head, int n)
{
    struct list **pp;
    struct list *new;

    new = malloc( sizeof(*new) );
    new->n = n;

    pp = head;
    while(*pp)
    {
        if( (*pp)->n >= n )
        {
            break;
        }

        pp = &((*pp)->next);
    }

    new->next = *pp;
    *pp = new;
}

// Problem 7.
//
// Write an function which given a list, rearranges its nodes so they are sorted
// in increasing order. It should use insert_sorted().
void sort(struct list **head)
{
}

// Problem 8.
//
// Write an Append() function that takes two lists, 'a' and 'b', appends 'b' onto
// the end of 'a', and then sets 'b' to NULL
void append(struct list **head1, struct list **head2)
{
    struct list **pp;
    pp = head1;

    while(*pp)
    {
        pp = &((*pp)->next);
    }
    *pp = *head2;
    *head2 = NULL;
}

// Problem 9.
//
// Given a list, split it into two sublists — one for the front half, and
// one for the back half. If
// the number of elements is odd, the extra element should go in the front list. 
//
// List in argument is first half. Returned list is a second half.
// We need double pointer for list because we modify it by cutting it's tail.
struct list *split(struct list **head)
{
    struct list *half;
    struct list **pp;
    int count;

    pp = head;
    count = 0;
    while(*pp)
    {
        count++;
        pp = &((*pp)->next);
    }

    // Divide and get bigger half
    // count = 9 - 9/2 = 9 - 4 = 5
    count = count - count/2;

    pp = head;
    while(count--)
    {
        pp = &((*pp)->next);
    }

    // FIXME
    // Bad thing about this is that caller must free this memory :-(
    half = malloc( sizeof(*half) );
    half = *pp;
    *pp = NULL;

    return half;
}

// Split list using tricky technique with 2 pointers.
// First pointer goes 1 node at time, second pointer goes 2 nodes at time. When
// second pointer reaches the end, first pointer will point in middle.
//
// It's not cheaper, because this algorithm has complexity O(1.5N) that is
// exactly as in simple algorithm.
void split_tricky(struct list **head, struct list **half)
{
    struct list **p1, *p2;

    p1 = head;
    p2 = *head;
    while(p2)
    {
        p1 = &((*p1)->next);
        p2 = p2->next;
        if(p2)
            p2 = p2->next;
    }

    *half = *p1;
    *p1 = NULL;
}

int main(int argc, const char *argv[])
{
    struct list *head = NULL;
    struct list *head2 = NULL;

    head = list_constructor_tail(13);
    list_print(head);

    head2 = malloc( sizeof(*head2) );
    split_tricky( &head, &head2 );

    list_print(head);
    list_print(head2);

    free(head2);
    
    return 0;
}
