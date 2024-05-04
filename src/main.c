#include <stdio.h>
#include <stdlib.h>
#include "client.h"

int main(int argc, char **argv) {
    Client *client = parseArguments(argc, argv);

    while (1) {
        handleMenuOption(client);
    }

    return 0;
}