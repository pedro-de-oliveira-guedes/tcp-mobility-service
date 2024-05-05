#include "network_config.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <sys/socket.h>

void logError(char *message) {
    perror(message);

    exit(EXIT_FAILURE);
}

int clientSocketInit(char *ipVersion, char *ipAddress, uint16_t port, struct sockaddr_storage *storage) {
    if (ipVersion == NULL || ipAddress == NULL || port == 0 || storage == NULL) {
        return -1;
    }

    memset(storage, 0, sizeof(struct sockaddr_storage)); // Clears the storage structure

    struct in_addr hostAddrIpv4; // Stores the IPv4 address in network byte order
    // Checks if the IP version is IPv4 and the IP address is valid, if so, it parses the IP address and port
    if (strcmp(ipVersion, "ipv4") == 0 && inet_pton(AF_INET, ipAddress, &hostAddrIpv4)) {
        struct sockaddr_in *ipv4 = (struct sockaddr_in *) storage;

        ipv4->sin_family = AF_INET; // Sets the address family to IPv4
        ipv4->sin_port = htons(port); // Sets the port number
        ipv4->sin_addr = hostAddrIpv4; // Sets the IP address

        return 0;
    }

    struct in6_addr hostAddrIpv6; // Stores the IPv6 address in network byte order
    // Checks if the IP version is IPv6 and the IP address is valid, if so, it parses the IP address and port
    if (strcmp(ipVersion, "ipv6") == 0 && inet_pton(AF_INET6, ipAddress, &hostAddrIpv6)) {
        struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *) storage;

        ipv6->sin6_family = AF_INET6; // Sets the address family to IPv6
        ipv6->sin6_port = htons(port); // Sets the port number
        memcpy(&(ipv6->sin6_addr), &hostAddrIpv6, sizeof(hostAddrIpv6)); // Sets the IP address

        return 0;
    }

    return -1;
}

int convertAddressToString(struct sockaddr *address, char *str, size_t strSize) {
    if (address == NULL || str == NULL) {
        return -1;
    }

    char addrStr[INET6_ADDRSTRLEN + 1] = "";

    if (address->sa_family == AF_INET) {
        struct sockaddr_in *ipv4 = (struct sockaddr_in *) address;

        // Convert the IP address to a string
        if (!inet_ntop(AF_INET, &(ipv4->sin_addr), addrStr, INET6_ADDRSTRLEN + 1))
            return -1;

        // Formats the IP Address string
        snprintf(str, strSize, "IPv4 %s %hu", addrStr, ntohs(ipv4->sin_port));

        return 0;
    }

    if (address->sa_family == AF_INET6) {
        struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *) address;

        // Convert the IP address to a string
        if (!inet_ntop(AF_INET6, &(ipv6->sin6_addr), addrStr, INET6_ADDRSTRLEN + 1))
            return -1;

        // Formats the IP Address string
        snprintf(str, strSize, "IPv6 %s %hu", addrStr, ntohs(ipv6->sin6_port));

        return 0;
    }

    return -1;
}

int serverSocketInit(char *ipVersion, uint16_t port, struct sockaddr_storage *storage) {
    if (ipVersion == NULL || port == 0 || storage == NULL) {
        return -1;
    }

    memset(storage, 0, sizeof(struct sockaddr_storage)); // Clears the storage structure

    if (strcmp(ipVersion, "ipv4") == 0) {
        struct sockaddr_in *ipv4 = (struct sockaddr_in *) storage;

        ipv4->sin_family = AF_INET; // Sets the address family to IPv4
        ipv4->sin_port = htons(port); // Sets the port number
        ipv4->sin_addr.s_addr = INADDR_ANY; // Sets the IP address to any available address

        return 0;
    }

    if (strcmp(ipVersion, "ipv6") == 0) {
        struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *) storage;

        ipv6->sin6_family = AF_INET6; // Sets the address family to IPv6
        ipv6->sin6_port = htons(port); // Sets the port number
        ipv6->sin6_addr = in6addr_any; // Sets the IP address to any available address

        return 0;
    }

    return -1;
}