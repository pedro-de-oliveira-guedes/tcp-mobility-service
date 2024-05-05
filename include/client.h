//---------------------------------------------------------------------
// File	    : client.h
// Content	: Client definitions
// Author	: Pedro de Oliveira Guedes
//---------------------------------------------------------------------

#ifndef CLIENT
#define CLIENT

#include "coordinates.h"

#include <arpa/inet.h>

typedef struct {
    Coordinates coordinates;
    
    struct sockaddr_storage storage;

    int socket;
} Client;

Client* createClient(char *ipVersion, char *ipAddress, int port);
void printClientUsage();
Client* parseClientArguments(int argc, char **argv);
void printMenu();
void handleMenuOption(Client *client);
void handleRideRequest(Client *client);
void handleExit();

#endif