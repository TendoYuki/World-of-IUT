#ifndef LOCATION_H
#define LOCATION_H
#include <stdlib.h>
#include "exits.h"
#include "types.h"

extern const int MAX_OBJECT_PER_ROOM;
extern const int DIRECTION_COUNT;


/**
 * Creates and returns a newly allocated location with malloc()
*/
Location *LocationNew(char *name, char *desc);

/**
 * Destroys and deallocates a location passed in parameter
*/
void LocationDelete(Location *location);

/**
 * Displays in the terminal a location passed in parameter
*/
void LocationPrint(Location *location);

/**
 * Displays shortly in the terminal a location passed in parameter
*/
void LocationPrintShort(Location *location);

/**
 * Creates and allocates all locations available, returns the first location
*/
Location *LocationInit(Game *game);

/**
 * Destroys and deallocates all locations available
*/
void LocationDestroy(Game *game);

#endif