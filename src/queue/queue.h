/**
 * @file queue.h
 * @brief Provides a generic queue implementation for storing and managing data dynamically.
 * 
 * This header defines the structures and functions required to create, manage,
 * and free a generic queue.
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stddef.h>

#define ANY_PTR void * /**< Alias for a generic pointer to any data type. */

/**
 * @struct QueueNode
 * @brief Represents an individual node in the queue.
 * 
 * Each node contains:
 * - `data`: A pointer to the data stored in the node.
 * - `next`: A pointer to the next node in the queue.
 */
typedef struct QueueNode {
    void *data; /**< Pointer to the data stored in this node. */
    struct QueueNode *next; /**< Pointer to the next node. */
} QueueNode;

/**
 * @struct Queue
 * @brief Represents the queue structure.
 * 
 * The queue is managed using a linked list where `head` points to the
 * first node (front) and `tail` points to the last node (rear).
 * The `size` indicates the number of elements currently in the queue,
 * and `data_size` specifies the size in bytes of the data stored in each node.
 */
typedef struct Queue {
    QueueNode *head; /**< Pointer to the first node in the queue. */
    QueueNode *tail; /**< Pointer to the last node in the queue. */
    size_t size; /**< Number of elements in the queue. */
    size_t data_size; /**< Size of the data stored in each node, in bytes. */
} Queue;

/**
 * @brief Creates a new queue capable of storing data of the specified size.
 * 
 * This function initializes an empty queue and allocates memory for its structure.
 * 
 * @param data_size The size (in bytes) of the data to be stored in each node.
 * @return A pointer to the dynamically created `Queue` structure, or `NULL` if memory allocation fails.
 */
Queue *queue_create(size_t data_size);

/**
 * @brief Adds a new element to the rear of the queue.
 * 
 * This function creates a new queue node, stores the provided data in it, and
 * adds it to the end of the queue.
 * 
 * @param queue A pointer to the queue where the element will be added.
 * @param data A pointer to the data to be stored in the queue.
 * @return `true` if the operation succeeds, `false` otherwise.
 */
bool queue_push(Queue *queue, const ANY_PTR data);

/**
 * @brief Removes and retrieves the element at the front of the queue.
 * 
 * This function removes the node at the front of the queue and returns a pointer
 * to its data. The caller must ensure proper handling of the returned pointer.
 * 
 * @param queue A pointer to the queue from which the element will be removed.
 * @return A pointer to the data of the removed element, or `NULL` if the queue is empty.
 */
ANY_PTR queue_pop(Queue *queue);

/**
 * @brief Checks if the queue is empty.
 * 
 * Determines whether the queue contains any elements.
 * 
 * @param queue A pointer to the queue to check.
 * @return `true` if the queue is empty, `false` otherwise.
 */
bool queue_is_empty(const Queue *queue);

/**
 * @brief Frees all resources associated with a queue.
 * 
 * This function removes all nodes from the queue and deallocates its memory.
 * The queue pointer is set to `NULL` after freeing.
 * 
 * @param queue A double pointer to the `Queue` structure to be freed.
 */
void queue_free(Queue **queue);

#endif // QUEUE_H
