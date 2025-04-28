/**
 * @file client.h
 * @brief Header file for the client module.
 *
 * This file declares the interface for initializing a multithreaded client
 * system that processes output messages stored in a blocking queue and sends
 * them to their destination routers.
 */

#ifndef CLIENT_H
#define CLIENT_H

#include "../blocking-queue/blocking-queue.h"

/**
 * @brief Global blocking queue for outgoing messages.
 *
 * This queue is used to store messages that need to be sent by the client.
 * Each message is retrieved and delivered to its destination by the
 * multithreaded client.
 */
extern BlockingQueue *OutputQueue;

/**
 * @brief Initializes the multithreaded client.
 *
 * Creates a dedicated thread that continuously retrieves messages
 * from the `OutputQueue` and sends them to their designated router
 * based on the message's metadata.
 *
 * @note This function creates a detached thread to handle message delivery
 * independently of the main execution flow.
 */
void init_multithread_client();

#endif // CLIENT_H
