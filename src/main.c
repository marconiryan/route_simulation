#include <stdio.h>

#define ROUTER_CONFIG_PATH "../roteador.config"
#define LINKS_CONFIG_PATH "../enlaces.config"

const char *ID;

void line_separator() {
    printf("----------------------------------------\n");
}

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

void read_links_config() {
    FILE *file = fopen(LINKS_CONFIG_PATH, "r");
    if (!file) {
        fprintf(stderr, "Error opening '%s' file\n", LINKS_CONFIG_PATH);
        return;
    }

    int id_from, id_to, cost;
    int found = 0;

    while (fscanf(file, "%d %d %d", &id_from, &id_to, &cost) == 3) {
        line_separator();
        printf("ID from: %d\n", id_from);
        printf("ID to: %d\n", id_to);
        printf("Cost: %d \n", cost);
        found++;
    }

    fclose(file);
}

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
