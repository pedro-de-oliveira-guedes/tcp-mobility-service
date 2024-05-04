#include <stdio.h>
#include <stdlib.h>
#include "server.h"

int main(int argc, char **argv) {
    Server *server = parseServerArguments(argc, argv);
    Coordinates clientCoords = {0.0, 0.0};

    handleDriverOptions(&clientCoords, server);

    return 0;
}