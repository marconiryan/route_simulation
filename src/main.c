#include <stdio.h>
#include <stdlib.h>
#include "links/links.h"
#include "router/router.h"
#include "utils/utils.h"
#include "server/server.h"

int SERVER_ID;

int main(const int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: Please provide an ID as an argument.\n");
        return 1;
    }

    SERVER_ID = atoi(argv[1]);

    printf("Hello, Router ID: %d\n\n", SERVER_ID);
    line_separator();
    read_links_config();
    read_router_config();
    init_multithread_server();

    while (1) {

    }



    return 0;
}
