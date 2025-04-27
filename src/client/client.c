#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include "../router/router.h"
#include "../message/message.h"

#define BUFF_SIZE 1024
#define TIMEOUT_SECONDS 1


static void send_message(const Router *router, const char *message) {
    const int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Error creating the socket");
        exit(EXIT_FAILURE);
    }

    struct timeval timeout;
    timeout.tv_sec = TIMEOUT_SECONDS;
    timeout.tv_usec = 0;

    if (setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout)) < 0) {
        perror("Error setting send timeout");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(router->ip);
    server_addr.sin_port = htons(router->port);

    if (server_addr.sin_addr.s_addr == INADDR_NONE) {
        perror("Invalid IP address");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    const ssize_t bytes_sent = sendto(sockfd, message, strlen(message), 0, (struct sockaddr *) &server_addr,
                                      sizeof(server_addr));

    printf("Sent %zd bytes to %s:%d\n", bytes_sent, router->ip, router->port);
    printf("Message: %s\n", message);

    // TODO: Confirm that the message was delivered. Receive an OK?

    close(sockfd);
}

static void send_message_to_router_id(const int id, const char *message) {
    const Router *router = get_router_by_id(id);

    if (router == NULL) {
        fprintf(stderr, "Error: Router ID %d not found\n", id);
        return;
    }

    send_message(router, message);
}

static void check_output_messages() {
    const Message *message = blocking_queue_pop(OutputQueue);

    if (message->type != DATA) {
        return;
    }

    send_message_to_router_id(message->to_id, message->payload);
}

void init_multithread_client() {
    pthread_t thread_id;
    const int thread = pthread_create(&thread_id, NULL, check_output_messages, NULL);

    if (thread != 0) {
        perror("Error creating thread for client");
        exit(EXIT_FAILURE);
    }

    pthread_detach(thread_id);
}

