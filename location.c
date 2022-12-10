#include "location.h"
#include "stack.h"
#include "exits.h"
#include <string.h>
#include <stdio.h>
#include "game.h"

Location *LocationNew(char *name, char *desc) {
    Location *location;
    if (name && desc)
    {
        location=malloc(sizeof(Location));
        if(!location) return NULL;

        location->directions = malloc(sizeof(Location*) * 6);
        if(!location->directions) return NULL;

        for (int i = 0; i < 6 ; i++) {
            location->directions[i] = NULL;
        }

        location->name=strdup(name);
        location->desc=strdup(desc);
    }
    return location;
}

void LocationSetExit(Location *location, Direction direction, Location *destination) {
    switch(direction) {
        case NORTH:
            location->directions[0] = destination;
            break;
        case EAST:
            location->directions[1] = destination;
            break;
        case SOUTH:
            location->directions[2] = destination;
            break;
        case WEST:
            location->directions[3] = destination;
            break;
        case UP:
            location->directions[4] = destination;
            break;
        case DOWN:
            location->directions[5] = destination;
            break;
        default:
            return;
            break;
    }
}

void LocationDelete(Location *location) {
    if (location)
    {
        if (location->name) free(location->name);
        if (location->desc) free(location->desc);
        free(location);
    }
}

void LocationPrint(Location *location) {
    if (location) printf("%s\n%s\n",location->name,location->desc);
}

void LocationPrintShort(Location *location) {
    if (location) printf("%s\n%s\n",location->name,location->desc);
}

Location *LocationInit(Game* game) {
    Stack *locationStack;

    Location* attic = LocationNew("Attic", "EYS"); 
    locationStack = StackPush(locationStack, attic);


    Location* entrance = LocationNew("Entrance", "zef"); 
    locationStack = StackPush(locationStack, entrance);

    LocationSetExit(entrance, UP, attic);
    game->locationStack = locationStack;
    return entrance;
}

void LocationDestroy(Game* game) {
    Stack * temp = game->locationStack;
    while (!StackIsEmpty(temp))
    {
        LocationDelete(StackHead(temp));
        temp = StackPop(temp);
    }
}
