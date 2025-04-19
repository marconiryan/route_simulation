#include <stdio.h>
#include "router.h"
#include "../utils/utils.h"

#define ROUTER_CONFIG_PATH "../config/roteador.config"

void read_router_config() {
    FILE *file = fopen(ROUTER_CONFIG_PATH, "r");
    if (!file) {
        fprintf(stderr, "Error opening '%s' file\n", ROUTER_CONFIG_PATH);
        return;
    }

    int id, port;
    char ip[16];
    int found = 0;

    while (fscanf(file, "%d %d %15s", &id, &port, ip) == 3) {
        printf("Router ID: %d\n", id);
        printf("Port: %d\n", port);
        printf("IP: %s\n", ip);
        line_separator();
        found++;
    }

    fclose(file);
}
