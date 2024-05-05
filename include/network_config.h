#ifndef NETWORK_CONFIG
#define NETWORK_CONFIG

/**
 * @brief Parses the given IP address and port and stores the result in the provided sockaddr_storage structure.
 *
 * This function takes an IP version, IP address, port number, and a pointer to a sockaddr_storage structure.
 * It parses the IP address and port and stores the result in the sockaddr_storage structure.
 *
 * @param ipVersion The IP version (IPv4 or IPv6) to parse.
 * @param ipAddress The IP address to parse.
 * @param port The port number to parse.
 * @param storage A pointer to a sockaddr_storage structure to store the parsed result.
 * @return Returns 0 on success, or a negative value if an error occurs.
 */
int parseAddress(char *ipVersion, char *ipAddress, uint16_t port, struct sockaddr_storage *storage);

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

#endif