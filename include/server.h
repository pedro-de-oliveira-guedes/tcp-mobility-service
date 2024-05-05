//---------------------------------------------------------------------
// File	    : server.h
// Content	: Server definitions
// Author	: Pedro de Oliveira Guedes
//---------------------------------------------------------------------

#ifndef SERVER
#define SERVER

#include "coordinates.h"
#include <sys/socket.h>

typedef struct {
    Coordinates coordinates;
    double currentDistance;

    struct sockaddr_storage storage;

    int socket;
} Server;

Server* createServer(char *ipVersion, int port);
void printServerUsage();
Server* parseServerArguments(int argc, char **argv);
void printRideOptions(Coordinates *clientCoords, Server *server);
void handleDriverOptions(Coordinates *clientCoords, Server *server);
void handleAcceptRide();
void handleRejectRide();

#endif