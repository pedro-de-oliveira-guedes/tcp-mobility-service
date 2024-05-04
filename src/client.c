#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Client* createClient(char *ipVersion, char *ipAddress, int port) {
    Client *client = (Client *) malloc(sizeof(Client));

    client->coordinates.latitude = 0.0;
    client->coordinates.longitude = 0.0;
    client->ipVersion = ipVersion;
    client->ipAddress = ipAddress;
    client->port = port;

    return client;
}

void printUsage() {
    printf("Usage: ./client <ipv4|ipv6> <ip_address> <port>\n");
    printf("Example: ./client ipv4 127.0.0.1 50501\n");
}

Client* parseArguments(int argc, char **argv) {
    if (argc != 3) {
        printUsage();
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