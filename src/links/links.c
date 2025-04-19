#include <stdio.h>
#include "links.h"
#include "../utils/utils.h"

#define LINKS_CONFIG_PATH "../config/enlaces.config"

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
