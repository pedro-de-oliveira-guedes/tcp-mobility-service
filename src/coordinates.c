#include "coordinates.h"
#include <math.h>

#define PI 3.14159265358979323846
#define EARTH_RADIUS 6371.0

static double calculateHarversineDistance(Coordinates *c1, Coordinates *c2) {
    double latitudeDistance = (c2->latitude - c1->latitude) * PI / 180.0;
    double longitudeDistance = (c2->longitude - c1->longitude) * PI / 180.0;

    double latitudeRadians1 = c1->latitude * PI / 180.0;
    double latitudeRadians2 = c2->latitude * PI / 180.0;

    double a =  pow(sin(latitudeDistance / 2), 2) + 
                pow(sin(longitudeDistance / 2), 2) * 
                cos(latitudeRadians1) * cos(latitudeRadians2);

    double c = 2 * asin(sqrt(a));
    
    return EARTH_RADIUS * c;
}