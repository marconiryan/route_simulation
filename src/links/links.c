#include <stdio.h>
#include "links.h"

#include <stdlib.h>

#include "../utils/utils.h"

#define LINKS_CONFIG_PATH "../config/enlaces.config"

static void display_link(const Link *link) {
    printf("ID from: %d\n", link->from);
    printf("ID to: %d\n", link->to);
    printf("Cost: %d \n", link->cost);
}

static Link *create_link(const int from, const int to, const int cost) {
    Link *link = malloc(sizeof(Link));
    link->from = from;
    link->to = to;
    link->cost = cost;
    return link;
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
        Link *link = create_link(id_from, id_to, cost);

        if (!link) {
            continue;
        }

        display_link(link);
        free(link); // Prevent memory leak
        found++;
    }

    fclose(file);
}
