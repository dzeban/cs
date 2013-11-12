#include <stdio.h>  // printf
#include "slist.h"

#define N 10
#define I1 15
#define I2 32

int main(int argc, const char *argv[])
{
    struct list *head1, *head2;
    struct list *item;

    head1 = list_constructor_head(N);
    head2 = list_constructor_tail(N);

    printf("---------head 1-------\n");
    list_print(head1);
    printf("======================\n");
    printf("---------head 2-------\n");
    list_print(head2);
    printf("======================\n");

    list_add_head(I1, &head1);
    list_print(head1);
    printf("======================\n");

    list_add_tail(I2, head2);
    list_print(head2);
    
    item = list_search(N/2, head2); 
    if(item)
    {
        list_print(item);
    }

    list_remove(N/2, &head1);
    list_print(head1);

    return 0;
}
