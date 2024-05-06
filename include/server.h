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

/**
 * @brief Creates a new Server instance.
 *
 * @param ipVersion The IP version to use for the server.
 * @param port The port number to bind the server to.
 * @return A pointer to the newly created Server instance.
 */
Server* createServer(char *ipVersion, int port);

/**
 * @brief Prints the usage information for the server.
 */
void printServerUsage();

/**
 * @brief Parses the command line arguments and creates a new Server instance.
 *
 * @param argc The number of command line arguments.
 * @param argv The array of command line arguments.
 * @return A pointer to the newly created Server instance.
 */
Server* parseServerArguments(int argc, char **argv);

/**
 * @brief Prints the available ride options for a client at the given coordinates.
 *
 * @param clientCoords The coordinates of the client.
 * @param server The Server instance.
 */
void printRideOptions(Coordinates *clientCoords, Server *server);

/**
 * @brief Shows the driver the available options for the ride request, 
 * calling functions to handle the acceptance or rejection of the ride.
 * 
 * It also shows the distance between the client and the driver.
 *
 * @param clientCoords The coordinates of the client.
 * @param server The Server instance.
 */
void handleDriverOptions(Coordinates *clientCoords, Server *server, int clientSocket);

/**
 * @brief Handles the acceptance of a ride request.
 */
void handleAcceptRide(Server *server, int clientSocket);

/**
 * @brief Handles the rejection of a ride request.
 */
void handleRejectRide(int clientSocket);

/**
 * @brief Sets up the server by binding it to a port, listening for incoming connections and showing the connection address.
 *
 * @param server The Server instance.
 * @return 0 if the server was successfully set up, -1 otherwise.
 */
int setupServer(Server *server);

/**
 * @brief Receives a client connection request, accepts it, prints the client address and returns the client socket file descriptor.
 *
 * @param server The Server instance.
 * @return The client socket file descriptor or -1 if an error occurred.
 */
int connectToClient(Server *server);

#endif