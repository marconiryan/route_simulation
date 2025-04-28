/**
 * @file server.h
 * @brief Provides the interface for the server's functionality, including routing configuration and multithreading initialization.
 *
 * This header defines the server's integration with the router configuration and exposes
 * a function to initialize a multi-thread server for handling incoming messages.
 */

#ifndef SERVER_H
#define SERVER_H

#include "../router/router.h"

/**
 * @brief The ID of the current server.
 *
 * This global variable represents the unique identifier of the server instance.
 * It is used to differentiate this server from other routers in the system.
 */
extern Router *SERVER_ROUTER;

/**
 * @brief Initializes a multi-thread UDP server.
 *
 * This function creates a separate thread to configure and run the server. The server
 * listens for incoming UDP messages on the IP and port specified in the `SERVER_ROUTER` configuration.
 * Messages will be received, processed, and responded to asynchronously in the thread.
 *
 * @note If the server thread cannot be created, the program will terminate with an error.
 * @warning Ensure that `SERVER_ROUTER` is properly initialized before calling this function.
 */
void init_multithread_server();

#endif // SERVER_H
