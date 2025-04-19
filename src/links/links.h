#ifndef LINKS_H
#define LINKS_H

typedef struct {
    int from;
    int to;
    int cost;
} Link;


void read_links_config();

#endif //LINKS_H
