#ifndef SERVER_H
#define SERVER_H

#include "../router/router.h"

extern Router *SERVER_ROUTER;

void init_multithread_server();

#endif //SERVER_H
