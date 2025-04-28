#include "blocking-queue.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

BlockingQueue *blocking_queue_create(const size_t data_size) {
    BlockingQueue *bq = malloc(sizeof(BlockingQueue));
    if (bq == NULL) {
        return NULL;
    }

    bq->queue = queue_create(data_size);
    if (bq->queue == NULL) {
        free(bq);
        return NULL;
    }

    pthread_mutex_init(&bq->mutex, NULL);
    pthread_cond_init(&bq->cond, NULL);

    return bq;
}

void blocking_queue_free(BlockingQueue **bq) {
    if (bq == NULL || *bq == NULL) {
        return;
    }

    queue_free(&(*bq)->queue);
    pthread_mutex_destroy(&(*bq)->mutex);
    pthread_cond_destroy(&(*bq)->cond);
    free(*bq);
    *bq = NULL;
}

bool blocking_queue_push(BlockingQueue *bq, const ANY_PTR data) {
    if (bq == NULL || data == NULL) {
        return false;
    }

    pthread_mutex_lock(&bq->mutex);

    bool const success = queue_push(bq->queue, data);

    pthread_cond_signal(&bq->cond);
    pthread_mutex_unlock(&bq->mutex);

    return success;
}

ANY_PTR blocking_queue_pop(BlockingQueue *bq) {
    if (bq == NULL) {
        return NULL;
    }

    pthread_mutex_lock(&bq->mutex);

    while (queue_is_empty(bq->queue)) {
        pthread_cond_wait(&bq->cond, &bq->mutex);
    }

    ANY_PTR data = queue_pop(bq->queue);

    pthread_mutex_unlock(&bq->mutex);

    return data;
}
