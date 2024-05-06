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
    if (socketAddressResult == -1) {
        logError("Erro ao inicializar o socket do servidor");
    }

    // Creates a socket for TCP communication. The TCP is defined by SOCK_STREAM.
    server->socket = socket(server->storage.ss_family, SOCK_STREAM, 0);
    if (server->socket == -1) {
        logError("Erro ao criar o socket do servidor");
    }

    // Allows the server to reuse the port number immediately after it is terminated.
    if (setsockopt(server->socket, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) == -1) {
        logError("Erro ao configurar a reutilização do endereço e porta do servidor");
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

void handleDriverOptions(Coordinates *clientCoords, Server *server, int clientSocket) {
    int option;

    printRideOptions(clientCoords, server);
    printf("Digite a opção desejada: ");
    scanf("%d", &option);

    switch (option) {
        case 0:
            handleRejectRide(clientSocket);
            break;
        case 1:
            handleAcceptRide(server, clientSocket);
            break;
        default:
            printf("\nOpção inválida!\n");
            break;
    }
}

void updateDriverDistance(Server *server, int clientSocket) {
    while (server->currentDistance >= 0.0) {
        // Sends the current distance to the client.
        if (send(clientSocket, &server->currentDistance, sizeof(double), 0) == -1) {
            logError("Erro ao enviar a distância atual do motorista para o cliente");
        }

        server->currentDistance -= 400.0;
        sleep(2);
    }

    // Sends the negative or zero distance to the client, confirming the arrival of the driver
    if (send(clientSocket, &server->currentDistance, sizeof(double), 0) == -1) {
        logError("Erro ao enviar a confirmação de chegada ao destino para o cliente");
    }
}

void handleAcceptRide(Server *server, int clientSocket) {
    printf("\nCorrida aceita!\n");

    // Sends the driver confirmation to the client.
    int rideAccepted = 1;
    if (send(clientSocket, &rideAccepted, sizeof(int), 0) == -1) {
        logError("Erro ao enviar a confirmação da corrida para o cliente");
    }

    updateDriverDistance(server, clientSocket);
    
    printf("\nVocê chegou ao seu destino!\n");
    close(clientSocket);
}

void handleRejectRide(int clientSocket) {
    printf("\nCorrida rejeitada!\n");

    // Sends the driver rejection to the client.
    int rideRejected = 0;
    if (send(clientSocket, &rideRejected, sizeof(int), 0) == -1) {
        logError("Erro ao enviar a rejeição da corrida para o cliente");
    }

    close(clientSocket);
}

int setupServer(Server *server) {
    // Binds the server socket to the specified address.
    if (bind(server->socket, (struct sockaddr *)&server->storage, sizeof(server->storage)) == -1) {
        return -1;
    }

    // Listens for incoming connections on the server socket.
    if (listen(server->socket, 1) == -1) {
        return -1;
    }

    // Formats the connection address to string and prints it.
    char serverAddress[BUFF_SIZE];
    if (0 != convertAddressToString((struct sockaddr *)&server->storage, serverAddress, BUFF_SIZE)) {
        return -1;
    }
    printf("Servidor escutando em %s\n", serverAddress);

    return 0;
}

int connectToClient(Server *server) {
    struct sockaddr_storage clientStorage;
    socklen_t clientStorageSize = sizeof(clientStorage);

    // Accepts the client connection request.
    int clientSocket = accept(server->socket, (struct sockaddr *)&clientStorage, &clientStorageSize);

    // Formats the connection address to string and prints it.
    char clientAddress[BUFF_SIZE];
    if (0 != convertAddressToString((struct sockaddr *)&clientStorage, clientAddress, BUFF_SIZE)) {
        return -1;
    }
    printf("Conexão aceita de %s\n", clientAddress);

    return clientSocket;
}

int main(int argc, char **argv) {
    Server *server = parseServerArguments(argc, argv);

    if (setupServer(server) == -1) {
        logError("Erro ao configurar o servidor");
    }

    while (1) {
        printf("\nAguardando solicitação de corrida...\n");

        int clientSocket = connectToClient(server);
        if (clientSocket == -1) {
            logError("Erro ao conectar com o cliente");
        }

        // Receives the client coordinates.
        Coordinates clientCoords;
        if (recv(clientSocket, &clientCoords, sizeof(Coordinates), 0) == -1) {
            logError("Erro ao receber as coordenadas do cliente");
        }

        handleDriverOptions(&clientCoords, server, clientSocket);
    }

    close(server->socket);

    return 0;
}
