//---------------------------------------------------------------------
// File	    : network_config.h
// Content	: Network configuration header file.
// Author	: Pedro de Oliveira Guedes
//---------------------------------------------------------------------

#ifndef NETWORK_CONFIG
#define NETWORK_CONFIG

/**
 * @brief Initializes a client socket with the specified IP version, IP address, port, and storage.
 * 
 * This function parses the given IP version, IP address and port number, initializing the client socket.
 *
 * @param ipVersion The IP version to use (e.g., "IPv4" or "IPv6").
 * @param ipAddress The IP address to connect to.
 * @param port The port number to connect to.
 * @param storage A pointer to a sockaddr_storage structure to store the socket address information.
 * @return An integer representing the status of the socket initialization. Returns 0 on success, or a negative value on failure.
 */
int clientSocketInit(char *ipVersion, char *ipAddress, uint16_t port, struct sockaddr_storage *storage);

/**
 * @brief Converts the given sockaddr structure to a string.
 *
 * This function takes a sockaddr structure and converts it to a string.
 *
 * @param address The sockaddr structure to convert.
 * @param str The string to store the result.
 * @param strSize The size of the string.
 * @return Returns 0 on success, or a negative value if an error occurs.
 */
int convertAddressToString(struct sockaddr *address, char *str, size_t strSize);

/**
 * @brief Initializes a server socket address structure.
 *
 * This function initializes the server socket address structure with the given IP version and port number.
 * It uses every available IP address on the server as the connection address.
 *
 * @param ipVersion The IP version (IPv4 or IPv6) to use.
 * @param port The port number to use.
 * @param storage A pointer to a sockaddr_storage structure to store the result.
 * @return Returns 0 on success, or a negative value if an error occurs.
 */
int serverSocketInit(char *ipVersion, uint16_t port, struct sockaddr_storage *storage);

#endif