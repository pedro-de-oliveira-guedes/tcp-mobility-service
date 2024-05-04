#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printUsage() {
    printf("Usage: ./client <ipv4|ipv6> <ip_address> <port>\n");
    printf("Example: ./client ipv4 127.0.0.1 50501");
}

void parseArguments(int argc, char **argv, Client *client) {
    if (argc != 3) {
        printUsage();
        exit(1);
    }

    client->ipVersion = argv[1];
    client->ipAddress = argv[2];
    client->port = atoi(argv[3]);
}

void printMenu() {
    printf("========================== MENU CLIENTE ==========================\n");
    printf("| 0 - Sair do aplicativo                                         |\n");
    printf("| 1 - Solicitar corrida                                          |\n");
    printf("==================================================================\n");
}