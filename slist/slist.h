#ifndef LIST_H
#define LIST_H

struct list {
    int n;
    struct list *next;
};

void list_add_head(int i, struct list **head);
void list_add_tail(int i, struct list *head);
struct list *list_search(int n, struct list *head);
void list_remove(int i, struct list **head);

struct list *list_constructor_head(int n);
struct list *list_constructor_tail(int n);
void list_print(struct list *head);

#endif // LIST_H
