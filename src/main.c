#include <stdio.h>
#include "links/links.h"
#include "router/router.h"
#include "utils/utils.h"

const char *ID;

int main(const int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: Please provide an ID as an argument.\n");
        return 1;
    }

    ID = argv[1];

    printf("Hello, Router ID: %s\n\n", ID);
    line_separator();
    read_router_config();
    read_links_config();

    return 0;
}
