#include "server.h"
#include "network_config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFF_SIZE 1024

Server* createServer(char *ipVersion, int port) {
    Server *server = (Server *) malloc(sizeof(Server));

    Coordinates coordinates = {-19.9227, -43.9451};
    server->coordinates = coordinates;

    // Initializes the server socket address with the specified IP version and port.
    int socketAddressResult = serverSocketInit(ipVersion, (uint16_t)port, &server->storage);
    if (socketAddressResult < 0) {
        logError("Erro ao inicializar o socket do servidor");
    }

    // Creates a socket for TCP communication. The TCP is defined by SOCK_STREAM.
    server->socket = socket(server->storage.ss_family, SOCK_STREAM, 0);
    if (server->socket < 0) {
        logError("Erro ao criar o socket do servidor");
    }

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

int main(int argc, char **argv) {
    Server *server = parseServerArguments(argc, argv);

    // Binds the server socket to the specified address.
    if (bind(server->socket, (struct sockaddr *)&server->storage, sizeof(server->storage)) < 0) {
        logError("Erro ao vincular o socket do servidor ao endereço");
    }

    // Listens for incoming connections on the server socket.
    if (listen(server->socket, 1) < 0) {
        logError("Erro ao ouvir por conexões no socket do servidor");
    }

    // Formats the connection address to string and prints it.
    char serverAddress[BUFF_SIZE];
    if (0 != convertAddressToString((struct sockaddr *)&server->storage, serverAddress, BUFF_SIZE)) {
        logError("Erro ao converter o endereço do servidor para string");
    }
    printf("Servidor escutando em %s\n", serverAddress);

    while (1) {
        // Structures to store the client connection information.
        struct sockaddr_storage clientStorage;
        struct sockaddr *clientAddress = (struct sockaddr *)&clientStorage;

        // Accepts the client connection and stores the client address information.
        socklen_t addrlen = sizeof(clientStorage);
        int clientSocket = accept(server->socket, clientAddress, &addrlen);
        if (clientSocket < 0) {
            logError("Erro ao aceitar a conexão do cliente");
        }

        // Formats the client address to string and prints it.
        char clientAddressString[BUFF_SIZE];
        if (0 != convertAddressToString(clientAddress, clientAddressString, BUFF_SIZE)) {
            logError("Erro ao converter o endereço do cliente para string");
        }
        printf("Conexão aceita de %s\n", clientAddressString);

        // Receives the client coordinates.
        Coordinates clientCoords;
        if (recv(clientSocket, &clientCoords, sizeof(Coordinates), 0) == -1) {
            logError("Erro ao receber as coordenadas do cliente");
        }
        printf("Coordenadas do cliente: %.4f, %.4f\n", clientCoords.latitude, clientCoords.longitude);

        // Sends the driver coordinates to the client.
        if (send(clientSocket, &server->coordinates, sizeof(Coordinates), 0) == -1) {
            logError("Erro ao enviar as coordenadas do motorista para o cliente");
        }

        handleDriverOptions(&clientCoords, server);
    }

    close(server->socket);

    return 0;
}
