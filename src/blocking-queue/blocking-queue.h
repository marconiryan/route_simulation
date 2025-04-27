#ifndef BLOCKING_QUEUE_H
#define BLOCKING_QUEUE_H

#include "../queue/queue.h"
#include <pthread.h>

typedef struct {
    Queue *queue;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} BlockingQueue;

BlockingQueue* blocking_queue_create(size_t data_size);
void blocking_queue_free(BlockingQueue **bq);
bool blocking_queue_push(BlockingQueue *bq, const ANY_PTR data);
ANY_PTR blocking_queue_pop(BlockingQueue *bq);

#endif //BLOCKING_QUEUE_H
