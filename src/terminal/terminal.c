#include "terminal.h"
#include "../links/links.h"
#include "../message/message.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <bits/pthreadtypes.h>

#define SEND_MESSAGE_OPTION 1
#define EXIT_OPTION 2

static void display_menu() {
    usleep(500 * 1000);
    printf("\n========= MENU =========\n");
    printf("1. Send message to neighbor\n");
    printf("2. Exit\n");
    printf("========================\n");
    printf("Choose an option: ");
}

static void display_neighbors() {
    if (!has_neighbor(SERVER_ID)) {
        fprintf(stderr, "No neighbors found\n");
        return;
    }

    const Link *neighbors = get_neighbors_by_id(SERVER_ID);
    printf("Available neighbors:\n");
    for (int i = 0; i < count_neighbors(SERVER_ID); i++) {
        printf("[%d] -> cost: %d\n", neighbors[i].to, neighbors[i].cost);
    }

    printf("========================\n");
    printf("Choose a neighbor: ");
}

static void send_message() {
    display_neighbors();
    int neighbor_id;
    scanf("%d", &neighbor_id);
    getchar();  //  Remove the '\n' character left in the input buffer by scanf to prevent issues with fgets()

    if (!is_neighbor(SERVER_ID, neighbor_id)) {
        fprintf(stderr, "The selected neighbor is invalid\n");
        return;
    }

    char message[PAYLOAD_SIZE];
    printf("Type the message: ");
    fgets(message, PAYLOAD_SIZE, stdin);
    enqueue_data_message(message, neighbor_id);
}

static bool option_handler() {
    int option;
    scanf("%d", &option);

    if (option == SEND_MESSAGE_OPTION) {
        send_message();
        return true;
    }

    if (option == EXIT_OPTION) {
        return false;
    }

    return true;
}

static bool show_terminal() {
    display_menu();
    return option_handler();
}

static void init_terminal() {
    while (show_terminal()) {
    }
}

void init_multithread_terminal() {
    pthread_t thread_id;
    const int thread = pthread_create(&thread_id, NULL, init_terminal, NULL);

    if (thread != 0) {
        perror("Error creating thread for terminal");
        exit(EXIT_FAILURE);
    }

    const int join_result = pthread_join(thread_id, NULL);
    if (join_result != 0) {
        perror("Error waiting for thread");
        exit(EXIT_FAILURE);
    }
}
