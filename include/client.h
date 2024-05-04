//---------------------------------------------------------------------
// File	    : client.h
// Content	: Client definitions
// Author	: Pedro de Oliveira Guedes
//---------------------------------------------------------------------

#ifndef CLIENT
#define CLIENT

#include "coordinates.h"

typedef struct {
    Coordinates coordinates;
    char *ipVersion;
    char *ipAddress;
    int port;
} Client;

Client* createClient(char *ipVersion, char *ipAddress, int port);
void printUsage();
Client* parseArguments(int argc, char **argv);
void printMenu();
void handleMenuOption(Client *client);
void handleRideRequest(Client *client);
void handleExit();

#endif