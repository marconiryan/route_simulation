#include <stdio.h>
#include "router.h"
#include <stdlib.h>
#include <string.h>

#include "../utils/utils.h"

#define ROUTER_CONFIG_PATH "../config/roteador.config"

Router *SERVER_ROUTER = NULL;

static void display_router(const Router *router) {
    printf("ID: %d\n", router->id);
    printf("IP: %s\n", router->ip);
    printf("Port: %d\n", router->port);
    line_separator();
}

static Router *create_router(const int id, const char *ip, const int port) {
    Router *router = malloc(sizeof(Router));
    router->id = id;
    strcpy(router->ip, ip);
    router->port = port;
    return router;
}

void read_router_config() {
    FILE *file = fopen(ROUTER_CONFIG_PATH, "r");
    if (!file) {
        fprintf(stderr, "Error opening '%s' file\n", ROUTER_CONFIG_PATH);
        return;
    }

    int id, port;
    char ip[16];

    while (fscanf(file, "%d %d %15s", &id, &port, ip) == 3) {
        if (SERVER_ID == id) {
            SERVER_ROUTER = create_router(id, ip, port);
            display_router(SERVER_ROUTER);
        }
    }

    fclose(file);
}

void clear_router_config() {
    free(SERVER_ROUTER);
    SERVER_ROUTER = NULL;
}
