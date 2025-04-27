#ifndef MESSAGE_H
#define MESSAGE_H

#define PAYLOAD_SIZE 1000

#include "../blocking-queue/blocking-queue.h"

extern int SERVER_ID;
extern BlockingQueue *OutputQueue;

typedef enum {
    CONTROL = 0,
    DATA = 1
} MessageType;

typedef struct {
    MessageType type;
    int from_id;
    int to_id;
    char payload[PAYLOAD_SIZE];
} Message;

void enqueue_data_message(const char payload[PAYLOAD_SIZE], int to_id);

#endif //MESSAGE_H
