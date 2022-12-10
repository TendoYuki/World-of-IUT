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
/**
 * Binds a location to a direction of a certain other location
*/
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

    Location* OnTheRoad1 = LocationNew("The Road", "You are at the middle of a long road"); 
    locationStack = StackPush(locationStack, OnTheRoad1);

    Location* OnTheRoad2 = LocationNew("The Road", "You are at the end of a long road, something is blocking your path"); 
    locationStack = StackPush(locationStack, OnTheRoad2);

    Location* OnTheRoad3 = LocationNew("The Road", "You are at the end of a long road, something is blocking your path"); 
    locationStack = StackPush(locationStack, OnTheRoad3);

    Location* Frontyard = LocationNew("The Frontyard", "You are in the frontyard"); 
    locationStack = StackPush(locationStack, Frontyard);

    Location* Entrance = LocationNew("The Entrance", "You are at the entrance of the house"); 
    locationStack = StackPush(locationStack, Entrance);

    Location* DiningRoom = LocationNew("The Dining room", "You are in the dining room"); 
    locationStack = StackPush(locationStack, DiningRoom);

    Location* Kitchen = LocationNew("The Kitchen", "You are in the kitchen, please don't eat anything"); 
    locationStack = StackPush(locationStack, Kitchen);

    Location* LaundryRoom = LocationNew("The Laundry room", "You are in the laundry room,"); 
    locationStack = StackPush(locationStack, LaundryRoom);

    Location* Office = LocationNew("The Office", "You are in the office"); 
    locationStack = StackPush(locationStack, Office);

    Location* LivingRoom = LocationNew("The Living room", "You are in the living room, you cannot die in the living room..."); 
    locationStack = StackPush(locationStack, LivingRoom);

    Location* Attic = LocationNew("The Attic", "You are in the attic, only spiders and bats are there"); 
    locationStack = StackPush(locationStack, Attic);

    Location* Cellar = LocationNew("The Cellar", "You are in the cellar, nothing is there"); 
    locationStack = StackPush(locationStack, Cellar);

    // On the road 1
    LocationSetExit(OnTheRoad1, NORTH, OnTheRoad2);
    LocationSetExit(OnTheRoad1, SOUTH, OnTheRoad3);
    LocationSetExit(OnTheRoad1, WEST, Frontyard);

    // On the road 2
    LocationSetExit(OnTheRoad2, SOUTH, OnTheRoad1);

    // On the road 3
    LocationSetExit(OnTheRoad3, NORTH, OnTheRoad1);

    // In the frontyard
    LocationSetExit(Frontyard, WEST, Entrance);
    LocationSetExit(Frontyard, EAST, OnTheRoad1);

    // In the entrance
    LocationSetExit(Entrance, NORTH, DiningRoom);
    LocationSetExit(Entrance, UP, Attic);
    LocationSetExit(Entrance, DOWN, Cellar);
    LocationSetExit(Entrance, SOUTH, LivingRoom);
    LocationSetExit(Entrance, EAST, Frontyard);

    // In the dining room
    LocationSetExit(DiningRoom, SOUTH, Entrance);
    LocationSetExit(DiningRoom, WEST, Kitchen);

    // In the Kitchen
    LocationSetExit(Kitchen, EAST, DiningRoom);
    LocationSetExit(Kitchen, SOUTH, LaundryRoom);

    // In the laundry room
    LocationSetExit(LaundryRoom, NORTH, Kitchen);
    LocationSetExit(LaundryRoom, SOUTH, Office);

    // In the office
    LocationSetExit(Office, NORTH, LaundryRoom);
    LocationSetExit(Office, EAST, LivingRoom);
    
    // In the living room
    LocationSetExit(LivingRoom, WEST, Office);
    LocationSetExit(LivingRoom, NORTH, Entrance);

    // In the attic
    LocationSetExit(Attic, DOWN, Entrance);

    // In the cellar
    LocationSetExit(Cellar, UP, Entrance);
    

    game->locationStack = locationStack;
    return OnTheRoad1;
}

void LocationDestroy(Game* game) {
    Stack * temp = game->locationStack;
    while (!StackIsEmpty(temp))
    {
        LocationDelete(StackHead(temp));
        temp = StackPop(temp);
    }
}
