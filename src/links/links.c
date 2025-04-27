#include <stdio.h>
#include "links.h"

#include <stdlib.h>

#include "../utils/utils.h"
#include "../queue/queue.h"

#define LINKS_CONFIG_PATH "../config/enlaces.config"

Queue *Links = NULL;

static void display_link(const Link *link) {
    line_separator();
    printf("ID from: %d\n", link->from);
    printf("ID to: %d\n", link->to);
    printf("Cost: %d \n", link->cost);
}

static void display_links() {
    const QueueNode *current_node = Links->head;
    while (current_node != NULL) {
        const Link *link = (Link *) current_node->data;
        display_link(link);
        current_node = current_node->next;
    }
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

    Links = queue_create(sizeof(Link));

    while (fscanf(file, "%d %d %d", &id_from, &id_to, &cost) == 3) {
        Link *link = create_link(id_from, id_to, cost);

        if (!link) {
            continue;
        }

        queue_push(Links, link);
        found++;
    }

    display_links();

    fclose(file);
}

void clear_links_config() {
    queue_free(&Links);
}