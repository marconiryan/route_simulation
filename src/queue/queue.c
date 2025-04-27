#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static QueueNode* queue_node_create(const ANY_PTR data, const size_t data_size) {
    QueueNode *new_node = malloc(sizeof(QueueNode) + data_size);
    if (new_node == NULL) {
        return NULL;
    }

    new_node->data = (ANY_PTR)(new_node + 1);

    memcpy(new_node->data, data, data_size);
    new_node->next = NULL;

    return new_node;
}

Queue* queue_create(const size_t data_size) {
    if (data_size == 0) {
        return NULL;
    }

    Queue *queue = malloc(sizeof(Queue));
    if (queue == NULL) {
        return NULL;
    }

    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
    queue->data_size = data_size;

    return queue;
}

bool queue_push(Queue *queue, const ANY_PTR data) {
    if (queue == NULL || data == NULL) {
        return false;
    }

    QueueNode *new_node = queue_node_create(data, queue->data_size);
    if (new_node == NULL) {
        return false;
    }

    if (queue->tail != NULL) {
        queue->tail->next = new_node;
    } else {
        queue->head = new_node;
    }

    queue->tail = new_node;
    queue->size++;

    return true;
}

ANY_PTR queue_pop(Queue *queue) {
    if (queue == NULL || queue->head == NULL) {
        return NULL;
    }

    QueueNode *node_to_remove = queue->head;
    ANY_PTR data = node_to_remove->data;

    queue->head = node_to_remove->next;
    if (queue->head == NULL) {
        queue->tail = NULL;
    }

    free(node_to_remove);
    queue->size--;

    return data;
}

bool queue_is_empty(const Queue *queue) {
    if (queue == NULL) {
        return true;
    }

    return queue->size == 0;
}

void queue_free(Queue **queue) {
    if (queue == NULL || *queue == NULL) {
        return;
    }

    QueueNode *current_node = (*queue)->head;
    while (current_node != NULL) {
        QueueNode *next_node = current_node->next;
        free(current_node);
        current_node = next_node;
    }

    free(*queue);
    *queue = NULL;
}
