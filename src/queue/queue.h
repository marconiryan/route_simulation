#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stddef.h>

#define ANY_PTR void *

typedef struct QueueNode {
    void *data;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode *head;
    QueueNode *tail;
    size_t size;
    size_t data_size;
} Queue;

Queue* queue_create(size_t data_size);
bool queue_push(Queue *queue, const ANY_PTR data);
ANY_PTR queue_pop(Queue *queue);
bool queue_is_empty(const Queue *queue);
void queue_free(Queue **queue);

#endif //QUEUE_H
