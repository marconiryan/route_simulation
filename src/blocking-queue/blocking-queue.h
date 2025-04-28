/**
 * @file blocking-queue.h
 * @brief Provides a thread-safe blocking queue implementation.
 *
 * This header contains the declarations for a thread-safe blocking queue
 * that allows producer-consumer communication between threads using
 * mutex and condition variables.
 */

#ifndef BLOCKING_QUEUE_H
#define BLOCKING_QUEUE_H

#include "../queue/queue.h"
#include <pthread.h>

/**
 * @struct BlockingQueue
 * @brief Represents a thread-safe queue with mutexes and condition variables.
 */
typedef struct {
    Queue *queue; /**< The internal queue for storing data. */
    pthread_mutex_t mutex; /**< Mutex for thread synchronization. */
    pthread_cond_t cond; /**< Condition variable for signaling threads. */
} BlockingQueue;

/**
 * @brief Creates a new blocking queue.
 *
 * Allocates and initializes a blocking queue. The queue uses a
 * mutex and condition variable to synchronize thread operations.
 *
 * @param data_size The size of each element in the queue.
 * @return A pointer to the newly created `BlockingQueue`, or `NULL` if allocation fails.
 */
BlockingQueue *blocking_queue_create(size_t data_size);

/**
 * @brief Frees the resources associated with a blocking queue.
 *
 * Releases memory and cleans up the mutex and condition variable
 * used by the blocking queue.
 *
 * @param bq A pointer to the `BlockingQueue` pointer to be freed.
 */
void blocking_queue_free(BlockingQueue **bq);

/**
 * @brief Adds an element to the blocking queue in a thread-safe manner.
 *
 * Blocks if the queue is full until space becomes available.
 *
 * @param bq A pointer to the blocking queue.
 * @param data A pointer to the element to be added to the queue.
 * @return `true` if the data was successfully added, `false` otherwise.
 */
bool blocking_queue_push(BlockingQueue *bq, const ANY_PTR data);

/**
 * @brief Removes and returns an element from the blocking queue.
 *
 * Blocks if the queue is empty until data becomes available.
 *
 * @param bq A pointer to the blocking queue.
 * @return A pointer to the removed data. The caller is responsible for managing
 * the returned data's memory.
 */
ANY_PTR blocking_queue_pop(BlockingQueue *bq);

#endif // BLOCKING_QUEUE_H
