//---------------------------------------------------------------------
// File	    : coordinates.h
// Content	: Coordinates TAD definitions
// Author	: Pedro de Oliveira Guedes
//---------------------------------------------------------------------

#ifndef COORDINATES
#define COORDINATES

typedef struct {
    double latitude;
    double longitude;
} Coordinates;

static double calculateHarversineDistance(Coordinates *c1, Coordinates *c2);

#endif