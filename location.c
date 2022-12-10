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

    Location* OnTheRoad1 = LocationNew("On the road", "The road goes north and south, at the west you see the frontyard of a house"); 
    locationStack = StackPush(locationStack, OnTheRoad1);

    Location* OnTheRoad2 = LocationNew("On the road", "The road stops there the only way is going south"); 
    locationStack = StackPush(locationStack, OnTheRoad2);

    Location* OnTheRoad3 = LocationNew("On the road", "The road stops there the only way is going north"); 
    locationStack = StackPush(locationStack, OnTheRoad3);

    Location* Frontyard = LocationNew("Frontyard", "You see the entrance of the house at the west, at the east you can see a long road"); 
    locationStack = StackPush(locationStack, Frontyard);

    Location* Entrance = LocationNew("Entrance", "You are at the entrance of the house.\nYou see the dining room at the north\nYou see the living room at the south\nAbove you you see what seems to be the entrance to the Attic\nBelow you is a trapdoor that leads to the Cellar"); 
    locationStack = StackPush(locationStack, Entrance);

    Location* DiningRoom = LocationNew("Dining room", "You are in the dining room,\nYou see the kitchen at the west\nYou see the entrance at the south"); 
    locationStack = StackPush(locationStack, DiningRoom);

    Location* Kitchen = LocationNew("Kitchen", "You are in the kitchen, please don't eat anything\nYou see the laundry room at the south\nYou see the Dining room at the west"); 
    locationStack = StackPush(locationStack, Kitchen);

    Location* LaundryRoom = LocationNew("Laundry room", "You are in the laundry room,\nYou see the office at the south\nYou see the kitchen at the north"); 
    locationStack = StackPush(locationStack, LaundryRoom);

    Location* Office = LocationNew("Office", "You are in the office,\nYou see the living room at the east\nYou see the laundry room at the north"); 
    locationStack = StackPush(locationStack, Office);

    Location* LivingRoom = LocationNew("Living room", "You are in the living room, you cannot die in the living room...\nYou see the entrance at the north\nYou see the office at the west"); 
    locationStack = StackPush(locationStack, LivingRoom);

    Location* Attic = LocationNew("Attic", "You are in the attic, only spiders and bats are there\nYour only way out is going back down"); 
    locationStack = StackPush(locationStack, Attic);

    Location* Cellar = LocationNew("Cellar", "You are in the cellar, nothing is there\nYour only way out is going back up"); 
    locationStack = StackPush(locationStack, Cellar);

    LocationSetExit(OnTheRoad1, NORTH, OnTheRoad2);
    LocationSetExit(OnTheRoad1, SOUTH, OnTheRoad3);
    LocationSetExit(OnTheRoad1, WEST, Frontyard);
    LocationSetExit(OnTheRoad2, SOUTH, OnTheRoad1);
    LocationSetExit(OnTheRoad3, NORTH, OnTheRoad1);
    LocationSetExit(Frontyard, WEST, Entrance);
    LocationSetExit(Frontyard, EAST, OnTheRoad1);
    LocationSetExit(Entrance, NORTH, DiningRoom);
    LocationSetExit(Entrance, UP, Attic);
    LocationSetExit(Entrance, DOWN, Cellar);
    LocationSetExit(Entrance, SOUTH, LivingRoom);
    LocationSetExit(Entrance, EAST, Frontyard);
    LocationSetExit(DiningRoom, SOUTH, Entrance);
    LocationSetExit(DiningRoom, WEST, Kitchen);
    LocationSetExit(Kitchen, EAST, DiningRoom);
    LocationSetExit(Kitchen, SOUTH, LaundryRoom);
    LocationSetExit(LaundryRoom, NORTH, Kitchen);
    LocationSetExit(LaundryRoom, SOUTH, Office);
    LocationSetExit(Office, NORTH, LaundryRoom);
    LocationSetExit(Office, EAST, LivingRoom);
    LocationSetExit(LivingRoom, WEST, Office);
    LocationSetExit(LivingRoom, NORTH, Entrance);
    LocationSetExit(Attic, DOWN, Entrance);
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
