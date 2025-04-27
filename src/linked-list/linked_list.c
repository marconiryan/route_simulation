#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

LinkedList* list_create() {
    LinkedList* list = malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

static Node *create_node(const int value) {
    Node* node = malloc(sizeof(Node));
    node->data = value;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void list_append(LinkedList* list, const int value) {
    if (list == NULL) {
        return;
    }

    Node* node = create_node(value);

    const bool isFirstElement = list->head == NULL;
    if (isFirstElement) {
        list->head = node;
        list->tail = node;
        list->size++;
        return;
    }

    node->prev = list->tail;
    list->tail->next = node;
    list->tail = node;
    list->size++;
}

Node* list_find(const LinkedList* list, const int value) {
    if (list == NULL) {
        return NULL;
    }

    Node* current = list->head;

    while (current != NULL) {
        if (current->data == value) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

bool list_delete(LinkedList* list, const int value) {
    if (list == NULL) {
        return false;
    }

    Node* node = list_find(list, value);
    if (node == NULL) {
        return false;
    }

    if (node->prev != NULL) {
        node->prev->next = node->next;
    } else {
        list->head = node->next;
    }

    if (node->next != NULL) {
        node->next->prev = node->prev;
    } else {
        list->tail = node->prev;
    }

    free(node);
    list->size--;
    return true;
}

static void list_clear(LinkedList* list) {
    if (list == NULL) {
        return;
    }

    Node* current = list->head;

    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void list_free(LinkedList** list) {
    list_clear(*list);
    free(*list);
    *list = NULL;
}

Node* list_get_first(const LinkedList* list) {
    if (list == NULL) {
        return NULL;
    }

    return list->head;
}

Node* list_get_last(const LinkedList* list) {
    if (list == NULL) {
        return NULL;
    }

    return list->tail;
}

bool list_is_empty(const LinkedList* list) {
    return list == NULL || list->size == 0;
}

int list_size(const LinkedList* list) {
    if (list == NULL) {
        return 0;
    }

    return list->size;
}

void list_print(const LinkedList* list) {
    if (list == NULL) {
        return;
    }

    const Node* current = list->head;
    printf("List: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }

    printf("\n");
}
