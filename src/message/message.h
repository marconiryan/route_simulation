/**
 * @file message.h
 * @brief Defines the structure and operations for handling messages in the system.
 * 
 * This header provides the interface and structure for exchanging messages
 * between servers and routers. Messages can be of the type `CONTROL` or `DATA`
 * and are delivered through a thread-safe blocking queue.
 */

#ifndef MESSAGE_H
#define MESSAGE_H

#define PAYLOAD_SIZE 1000 /**< Maximum size of the payload in a message. */

#include "../blocking-queue/blocking-queue.h"

/**
 * @brief The ID of the current server.
 * 
 * The global variable `SERVER_ID` represents the unique identifier for the
 * current server instance in the system.
 */
extern int SERVER_ID;

/**
 * @brief The global output queue for messages.
 * 
 * The `OutputQueue` holds `Message` objects that are waiting to be processed
 * and sent to their designated recipients.
 */
extern BlockingQueue *OutputQueue;

/**
 * @enum MessageType
 * @brief Represents the type of message.
 * 
 * A message can either be of the type `CONTROL` (for control information) or
 * `DATA` (for payload delivery).
 */
typedef enum {
    CONTROL = 0, /**< Control message type (e.g., configuration changes). */
    DATA = 1 /**< Data message type for transmitting payloads. */
} MessageType;

/**
 * @struct Message
 * @brief Represents a message exchanged within the system.
 * 
 * Each message contains metadata like its type, the sender's ID, the recipient's ID,
 * and the data payload (up to `PAYLOAD_SIZE` bytes).
 */
typedef struct {
    MessageType type; /**< Type of the message (`CONTROL` or `DATA`). */
    int from_id; /**< The ID of the sender. */
    int to_id; /**< The ID of the recipient. */
    char payload[PAYLOAD_SIZE]; /**< The message payload data. */
} Message;

/**
 * @brief Enqueues a data message into the `OutputQueue`.
 * 
 * This function creates a `Message` object of type `DATA` and fills it with
 * the provided payload and recipient ID. The message is then pushed into the
 * global `OutputQueue` for processing and delivery.
 * 
 * @param payload The payload data to send (null-terminated string). If `NULL`, the payload will be empty.
 * @param to_id The recipient's ID to which the message will be sent.
 * 
 * @note The payload will be truncated if it exceeds `PAYLOAD_SIZE` minus one byte.
 */
void enqueue_data_message(const char payload[PAYLOAD_SIZE], int to_id);

#endif // MESSAGE_H
