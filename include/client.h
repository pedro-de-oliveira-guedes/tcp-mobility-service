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


void printUsage();
void parseArguments(int argc, char **argv, Client *client);
void printMenu();

#endif