#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#define PORT 12345
#define BUFF_SIZE 1024

static int configure_server() {
    const int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd < 0) {
        perror("Error creating the socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("Error binding the socket");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    return sockfd;
}

static void listen_messages(const int sockfd) {
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);

    while (1) {
        char buffer[BUFF_SIZE];
        printf("Waiting for messages on port %d...\n", PORT);
        memset(buffer, 0, BUFF_SIZE);

        ssize_t bytes_received = recvfrom(sockfd, buffer, BUFF_SIZE, 0, (struct sockaddr *) &client_addr, &addr_len);

        if (bytes_received < 0) {
            perror("Error receiving data");
            close(sockfd);
            exit(EXIT_FAILURE);
        }

        printf("Received %zd bytes from %s:%d\n", bytes_received, inet_ntoa(client_addr.sin_addr),
               ntohs(client_addr.sin_port));
        printf("Message: %s\n", buffer);

        const char *response = "Message successfully received\n";
        sendto(sockfd, response, strlen(response), 0, (struct sockaddr *) &client_addr, addr_len);
    }

    close(sockfd);
}

static void *init_server(void *arg) {
    const int sockfd = configure_server();
    listen_messages(sockfd);
    return NULL;
}

void init_multithread_server() {
    pthread_t thread_id;
    const int thread = pthread_create(&thread_id, NULL, init_server, NULL);

    if (thread != 0) {
        perror("Error creating thread for server");
        exit(EXIT_FAILURE);
    }

    pthread_detach(thread_id);
}
