#ifndef LIST_H
#define LIST_H

struct list {
    int n;
    struct list *next;
};

void list_push(int i, struct list **head);
void list_append(int i, struct list *head);
struct list *list_search(int n, struct list *head);
void list_remove(int i, struct list **head);

struct list *list_constructor_head(int n);
struct list *list_constructor_tail(int n);
struct list *list_constructor_dup(int n, int d);
struct list *list_constructor_va(int count, ...);
void list_print(struct list *head);
int list_length(struct list *head);

#endif // LIST_H
