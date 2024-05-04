#include <stdio.h>
#include <stdlib.h>
#include "coordinates.h"

int main() {
    Coordinates c1 = { 38.898556, -77.037852 };
    Coordinates c2 = { 38.897147, -77.043934 };

    double distance = calculateHarversineDistance(&c1, &c2);

    printf("Distance between c1 and c2: %f km\n", distance);

    return 0;
}