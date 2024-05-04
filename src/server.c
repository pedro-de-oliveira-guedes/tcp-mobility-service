#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Server* createServer(char *ipVersion, int port) {
    Server *server = (Server *) malloc(sizeof(Server));

    server->coordinates.latitude = -19.9227;
    server->coordinates.longitude = -43.9451;
    server->ipVersion = ipVersion;
    server->port = port;

    return server;
}

void printServerUsage() {
    printf("Usage: ./server <ipv4|ipv6> <port>\n");
    printf("Example: ./server ipv4 50501\n");
}

Server* parseServerArguments(int argc, char **argv) {
    if (argc != 3) {
        printServerUsage();
        exit(1);
    }

    return createServer(argv[1], atoi(argv[2]));
}

void printRideOptions(Coordinates *clientCoords, Server *server) {
    double distance = calculateHarversineDistance(clientCoords, &server->coordinates);
    server->currentDistance = distance;

    printf("========================== CORRIDA DISPONÍVEL ==========================\n");
    printf("| $ Solicitação a %.2f metros de distância do seu local atual.         |\n", distance);
    printf("| 0 - Rejeitar corrida                                                 |\n");
    printf("| 1 - Aceitar corrida                                                  |\n");
    printf("========================================================================\n");
}

void handleDriverOptions(Coordinates *clientCoords, Server *server) {
    int option;

    printRideOptions(clientCoords, server);
    printf("Digite a opção desejada: ");
    scanf("%d", &option);

    switch (option) {
        case 0:
            handleRejectRide();
            break;
        case 1:
            handleAcceptRide();
            break;
        default:
            printf("\nOpção inválida!\n");
            printRideOptions(clientCoords, server);
            break;
    }
}

void handleAcceptRide() {
    printf("\nCorrida aceita!\n");
}

void handleRejectRide() {
    printf("\nCorrida rejeitada!\n");
}