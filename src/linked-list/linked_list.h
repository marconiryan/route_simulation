#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int size;
} LinkedList;

LinkedList* list_create(void);
void list_free(LinkedList** list);
void list_append(LinkedList* list, int value);
bool list_delete(LinkedList* list, int value);
Node* list_find(const LinkedList* list, int value);
Node* list_get_first(const LinkedList* list);
Node* list_get_last(const LinkedList* list);
bool list_is_empty(const LinkedList* list);
int list_size(const LinkedList* list);

void list_print(const LinkedList* list);

#endif //LINKED_LIST_H
