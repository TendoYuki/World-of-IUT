#ifndef OBJECT_H
#define OBJECT_H
#include "types.h"
#include <stdbool.h>

/**
 * Creates and allocates a new object and returns it
 * -1 == Object on the player
 * 0..12 == Object on a location
*/
Object *ObjectNew(char *name, char *desc);

/**
 * Deletes and deallocates an object
*/
void ObjectDelete(Object *object);

/**
 * Adds an object to the inventory of the player if the inventory isn't full
 * Returns -1 if the item was not added, returns the index in the player inventory if it succeded
*/
int AddObjectToInventory(Mobile *player, Object *object);

/**
 * Adds an object to a location if the location isn't full
 * Returns -1 if the item was not added, returns the index in the location if it succeded
*/
int AddObjectToLocation(Location *location, Object *object);

/**
 * Checks if the object determined by its name is stored in the player's inventory, if it exists returns its index else if it isn't return -1
*/
int ObjectIsInPlayerInventory(Mobile* player, char *objectName);

/**
 * Checks if the object determined by its name is stored in the location if it exists returns its index else if it isn't return -1
*/
int ObjectIsInLocation(Location *location, char *objectName);

#endif