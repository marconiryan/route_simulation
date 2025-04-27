#include "terminal.h"
#include "../links/links.h"
#include "../message/message.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <bits/pthreadtypes.h>

#define SEND_MESSAGE_OPTION 1
#define EXIT_OPTION 2

static void display_menu() {
    printf("\n========= MENU =========\n");
    printf("1. Enviar mensagem para vizinho\n");
    printf("2. Sair\n");
    printf("========================\n");
    printf("Escolha uma opção: ");
}

static void display_neighbors() {
    if (!has_neighbor(SERVER_ID)) {
        printf("Nenhum vizinho encontrado\n");
        return;
    }

    const Link *neighbors = get_neighbors_by_id(SERVER_ID);
    printf("Vizinhos disponiveis:\n");
    for (int i = 0; i < count_neighbors(SERVER_ID); i++) {
        printf("[%d] -> custo: %d\n", neighbors[i].to, neighbors[i].cost);
    }
    printf("========================\n");
    printf("Escolha um vizinho: ");

}

static void send_message() {
    display_neighbors();
    int neighbor_id;
    scanf("%d", &neighbor_id);

    if (!is_neighbor(SERVER_ID, neighbor_id)) {
        printf("O vizinho selecionado é invalido");
        return;
    }

    char message[1024];
    printf("Digite a mensagem: ");
    scanf("%s", message);
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

bool show_terminal() {
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




