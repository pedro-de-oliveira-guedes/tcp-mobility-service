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
void printUsage();
Server* parseArguments(int argc, char **argv);
void printRideOptions(Coordinates *client, Server *server);
void handleAcceptRide();
void handleRejectRide();

#endif