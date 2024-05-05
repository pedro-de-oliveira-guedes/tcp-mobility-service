#include "client.h"
#include "network_config.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

Client* createClient(char *ipVersion, char *ipAddress, int port) {
    Client *client = (Client *) malloc(sizeof(Client));

    Coordinates coordinates = {-16.055684212815216, -45.14319316648692};
    client->coordinates = coordinates;

    struct sockaddr_storage socketStorage;
    clientSocketInit(ipVersion, ipAddress, (uint16_t)port, &socketStorage);

    return client;
}

void printClientUsage() {
    printf("Usage: ./client <ipv4|ipv6> <ip_address> <port>\n");
    printf("Example: ./client ipv4 127.0.0.1 50501\n");
}

Client* parseClientArguments(int argc, char **argv) {
    if (argc != 4) {
        printClientUsage();
        exit(1);
    }

    return createClient(argv[0], argv[1], atoi(argv[2]));
}

void printMenu() {
    printf("========================== MENU CLIENTE ==========================\n");
    printf("| 0 - Sair do aplicativo                                         |\n");
    printf("| 1 - Solicitar corrida                                          |\n");
    printf("==================================================================\n");
}

void handleMenuOption(Client *client) {
    int option;

    printMenu();
    printf("Digite a opção desejada: ");
    scanf("%d", &option);

    switch (option) {
        case 0:
            handleExit();
            break;
        case 1:
            handleRideRequest(client);
            break;
        default:
            printf("\nOpção inválida!\n");
            printMenu();
            break;
    }
}

void handleRideRequest(Client *client) {
    printf("Solicitando corrida...\n");
}

void handleExit() {
    printf("Saindo do aplicativo...\n");
    exit(0);
}
