#include <stdio.h>
#include <stdlib.h>
#include "blocking-queue/blocking-queue.h"
#include "client/client.h"
#include "links/links.h"
#include "message/message.h"
#include "router/router.h"
#include "utils/utils.h"
#include "server/server.h"
#include "terminal/terminal.h"

int SERVER_ID;

BlockingQueue *OutputQueue = NULL;
BlockingQueue *InputQueue = NULL;

int main(const int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Error: Please provide an ID as an argument.\n");
        return 1;
    }

    OutputQueue = blocking_queue_create(sizeof(Message));
    InputQueue = blocking_queue_create(sizeof(Message));

    SERVER_ID = atoi(argv[1]);

    printf("Hello, Router ID: %d\n\n", SERVER_ID);
    line_separator();
    read_links_config();
    read_router_config();
    init_multithread_server();
    init_multithread_client();
    init_multithread_terminal(); // blocking
    clear_router_config();
    clear_links_config();
    blocking_queue_free(&OutputQueue);
    blocking_queue_free(&InputQueue);

    return 0;
}
