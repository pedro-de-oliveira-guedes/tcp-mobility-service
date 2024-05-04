//---------------------------------------------------------------------
// File	    : server.h
// Content	: Server definitions
// Author	: Pedro de Oliveira Guedes
//---------------------------------------------------------------------

#ifndef SERVER
#define SERVER

#include "coordinates.h"

typedef struct {
    Coordinates coordinates;
    char *ipVersion;
    int port;
    double currentDistance;
} Server;

Server* createServer(char *ipVersion, int port);
void printServerUsage();
Server* parseServerArguments(int argc, char **argv);
void printRideOptions(Coordinates *clientCoords, Server *server);
void handleDriverOptions(Coordinates *clientCoords, Server *server);
void handleAcceptRide();
void handleRejectRide();

#endif