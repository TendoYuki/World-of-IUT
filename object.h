#ifndef OBJECT_H
#define OBJECT_H
#include "types.h"
#include <stdbool.h>

/**
 * Creates and allocates a new object and returns it
 * -1 == Object on the player
 * 0..12 == Object on a location
*/
Object *ObjectNew(char *name);

/**
 * Deletes and deallocates an object
*/
void ObjectDelete(Object *object);

/**
 * Adds an object to the inventory of the player if the inventory isn't full
 * Returns true if the item was successfully added, return false if it hasn't
*/
bool AddObjectToInventory(Mobile *player, Object *object);


/**
 * Checks if the object determined by its name is stored in the player's inventory, if it exists returns its index else if it isn't return -1
*/
int ObjectIsInPlayerInventory(Mobile* player, char *objectName);

/**
 * Checks if the object determined by its name is stored in the location if it exists returns its index else if it isn't return -1
*/
int ObjectIsInLocation(Location *location, char *objectName);

#endif