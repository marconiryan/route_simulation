#ifndef LINKS_H
#define LINKS_H
#include <stdbool.h>

typedef struct {
    int from;
    int to;
    int cost;
} Link;


void read_links_config();
void clear_links_config();
bool has_neighbor(int id);
int count_neighbors(int id);
Link *get_neighbors_by_id(int id);
Link *get_link_by_id(int id);
bool is_neighbor(int id_from, int id_to);

#endif //LINKS_H
