/**
 * @file terminal.h
 * @brief Provides an interactive terminal interface for sending messages and managing server neighbors.
 *
 * This header defines the functionality for initializing a multi-thread terminal
 * where users can interact with the server to send messages to its neighbors or exit.
 */

#ifndef TERMINAL_H
#define TERMINAL_H

/**
 * @brief The ID of the current server.
 *
 * `SERVER_ID` is a global variable representing the unique identifier of the server.
 * It is used to determine the neighbors of the server.
 */
extern int SERVER_ID;

/**
 * @brief Initializes the terminal module in a separate thread.
 *
 * This function creates a new thread to handle terminal-based user interactions.
 * Within the terminal, users can perform actions such as
 * - Sending messages to the server's neighbors.
 * - Exiting the application.
 *
 * The terminal will continuously run until the user chooses the exit option.
 *
 * @warning Ensure that the necessary modules (e.g., `links` and `message`) are properly initialized
 * before calling this function.
 *
 * @note If thread creation or execution fails, the application will terminate with an error.
 */
void init_multithread_terminal();

#endif // TERMINAL_H
