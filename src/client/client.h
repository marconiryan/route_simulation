#ifndef CLIENT_H
#define CLIENT_H

#include "../blocking-queue/blocking-queue.h"
extern BlockingQueue *OutputQueue;

void init_multithread_client();

#endif //CLIENT_H
