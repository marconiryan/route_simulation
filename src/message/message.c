#include "message.h"
#include <string.h>


void enqueue_data_message(const char payload[PAYLOAD_SIZE], const int to_id) {
    Message msg_data = {
        .type = DATA,
        .from_id = SERVER_ID,
        .to_id = to_id,
    };

    memset(msg_data.payload, 0, PAYLOAD_SIZE);
    if (payload != NULL) {
        const size_t payload_length = strlen(payload);
        const size_t copy_length = payload_length < PAYLOAD_SIZE ? payload_length : PAYLOAD_SIZE - 1;
        strncpy(msg_data.payload, payload, copy_length);
    }

    blocking_queue_push(OutputQueue, &msg_data);
}
