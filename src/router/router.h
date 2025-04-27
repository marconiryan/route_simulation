#ifndef ROUTER_H
#define ROUTER_H

extern int SERVER_ID;


typedef struct {
    int id;
    char ip[16];
    int port;
} Router;

void read_router_config();

void clear_router_config();

Router *get_router_by_id(int id);

#endif //ROUTER_H
