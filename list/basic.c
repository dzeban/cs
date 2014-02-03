#include <stdio.h>  // printf
#include "list.h"

int main(int argc, const char *argv[])
{
    struct list *head = NULL;

    head = list_constructor_head(10);
    list_push(13, &head);
    list_push(42, &(head->next));
    list_append(182, head);
    list_print(head);

    printf("Length: %d\n", list_length(head));

    return 0;
}
