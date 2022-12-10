#ifndef LOCATION_H
#define LOCATION_H
#include <stdlib.h>


/**
 * Location type having a name and a desctiption
 * Property Directions is a table of pointer locations, which each NULL Location represents the absence of one
 * The indexes of Directions correspond to the following
 * 0 -> north
 * 1 -> east
 * 2 -> south
 * 3 -> west
 * 4 -> up
 * 5 -> down
*/
typedef struct Location {
    char *name;
    char *desc;
    struct Location **directions;
    
} Location;


/**
 * Creates and returns a newly allocated location with malloc()
*/
Location *LocationNew(char *name, char *desc);

/**
 * Destroys and deallocates a location passed in parameter
*/
void LocationDelete(Location* location);

/**
 * Displays in the terminal a location passed in parameter
*/
void LocationPrint(Location* location);

/**
 * Displays shortly in the terminal a location passed in parameter
*/
void LocationPrintShort(Location* location);

/**
 * Creates and allocates all locations available, returns the first location
*/
Location *LocationInit();

/**
 * Destroys and deallocates all locations available
*/
void LocationDestroy();

#endif