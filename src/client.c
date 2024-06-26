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

#define BUFF_SIZE 1024

Client* createClient(char *ipVersion, char *ipAddress, int port) {
    Client *client = (Client *) malloc(sizeof(Client));

    Coordinates coordinates = {-19.930547371307195, -43.978467580237876};
    client->coordinates = coordinates;

    // Initializes the client socket address with the specified IP version, IP address and port.
    int socketAddressResult = clientSocketInit(ipVersion, ipAddress, (uint16_t)port, &client->storage);
    if (socketAddressResult == -1) {
        logError("Erro ao inicializar o socket do cliente");
    }

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

    return createClient(argv[1], argv[2], atoi(argv[3]));
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
            break;
    }
}

int connectToServer(Client *client) {
    // Creates a socket for TCP communication. The TCP is defined by SOCK_STREAM.
    client->currentServerSocket = socket(client->storage.ss_family, SOCK_STREAM, 0);
    if (client->currentServerSocket == -1) {
        logError("Erro ao criar o socket do cliente");
    }

    // Connects the client socket to the server socket.
    if (0 != connect(client->currentServerSocket, (struct sockaddr *)&client->storage, sizeof(client->storage))) {
        return -1;
    }

    // Formats the connection address to string and prints it.
    char connectedAddress[BUFF_SIZE];
    if (0 != convertAddressToString((struct sockaddr *)&client->storage, connectedAddress, BUFF_SIZE)) {
        return -1;
    }
    printf("Conectado ao servidor %s\n", connectedAddress);

    return 0;
}

void trackDriverLocation(Client *client) {
    double currentDistance;

    while (1) {
        if (recv(client->currentServerSocket, &currentDistance, sizeof(double), 0) == -1) {
            logError("Erro ao receber a distância atual do motorista");
        }

        if (currentDistance < 0.0) {
            break;
        }

        printf("Distância atual do motorista: %.2f metros\n", currentDistance);
    }

    printf("O motorista chegou até você!\n");
}

void handleRideRequest(Client *client) {
    printf("Solicitando corrida...\n");

    if (connectToServer(client) == -1) {
        logError("Erro ao conectar ao servidor");
    }
    
    // Sends the ride request to the server.
    if (send(client->currentServerSocket, &client->coordinates, sizeof(Coordinates), 0) == -1) {
        logError("Erro ao enviar a solicitação de corrida");
    }

    // Waits for the server response.
    int rideAccepted;
    if (recv(client->currentServerSocket, &rideAccepted, sizeof(int), 0) == -1) {
        logError("Erro ao receber a resposta do servidor");
    }

    if (rideAccepted) {
        printf("Corrida aceita!\n");

        trackDriverLocation(client);

        close(client->currentServerSocket);
        exit(0);
    } else {
        printf("Corrida rejeitada!\n");

        close(client->currentServerSocket);
    }
}

void handleExit() {
    printf("Saindo do aplicativo...\n");
    exit(0);
}

int main(int argc, char **argv) {
    Client *client = parseClientArguments(argc, argv);

    while (1) {
        handleMenuOption(client);
    }

    close(client->currentServerSocket);

    return 0;
}
