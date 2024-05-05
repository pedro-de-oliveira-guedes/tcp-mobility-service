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

/**
 * @brief Creates a new client with the specified IP version, IP address and port.
 *
 * @param ipVersion The IP version to use (e.g., "IPv4" or "IPv6").
 * @param ipAddress The IP address to connect to.
 * @param port The port number to connect to.
 * @return A pointer to the newly created Client object. The program is terminated if an error occurs.
 */
Client* createClient(char *ipVersion, char *ipAddress, int port);

/**
 * @brief Prints the usage instructions for the client program.
 */
void printClientUsage();

/**
 * @brief Parses the command line arguments and creates a Client object.
 *
 * @param argc The number of command line arguments.
 * @param argv An array of strings containing the command line arguments.
 * @return A pointer to the created Client object.
 */
Client* parseClientArguments(int argc, char **argv);

/**
 * @brief Prints the menu options for the client program.
 */
void printMenu();

/**
 * @brief Handles the selected menu option by performing the corresponding action.
 *
 * @param client A pointer to the Client object.
 */
void handleMenuOption(Client *client);

/**
 * @brief Connects the client to the server.
 *
 * @param client A pointer to the Client object.
 * @return 0 if the connection was successful, -1 otherwise.
 */
int connectToServer(Client *client);

/**
 * @brief Handles the ride request by sending it to the server.
 *
 * @param client A pointer to the Client object.
 */
void handleRideRequest(Client *client);

/**
 * @brief Handles the exit option by terminating the client program.
 */
void handleExit();

#endif