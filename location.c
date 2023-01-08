#include "location.h"
#include "exits.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "stack.h"
#include "object.h"

const int MAX_OBJECT_PER_ROOM = 6;
const int DIRECTION_COUNT = 6;

Location *LocationNew(char *name, char *desc) {
    Location *location = malloc(sizeof(Location));
    if(!location) return NULL;

    location->directions = malloc(sizeof(Location*) * DIRECTION_COUNT);
    if(!location->directions) return NULL;
    for (int i = 0; i < DIRECTION_COUNT; i++) location->directions[i] = NULL;
    
    location->objects = malloc(sizeof(Object*) * MAX_OBJECT_PER_ROOM);
    if(!location->objects) return NULL;
    for (int i = 0; i < MAX_OBJECT_PER_ROOM; i++) location->objects[i] = NULL;

    location->name = name ? strdup(name) : NULL;
    location->desc = desc ? strdup(desc) : NULL;
    return location;
}


/**
 * Binds a location to a direction of a certain other location
*/
void LocationSetExit(Location *location, Direction direction, Location *destination) {
    location->directions[direction] = destination;
}

void LocationDelete(Location *location) {
    if (location)
    {
        if (location->name) free(location->name);
        if (location->desc) free(location->desc);
        if (location->objects){
            for (int i=0;i<6;i++){
                if(location->objects[i]) free(location->objects[i]);
            }
            free(location->objects);
        }
        free(location);
    }
}

void LocationPrint(Location *location) {
    if (location) printf("%s\n%s\n",location->name,location->desc);
}

void LocationPrintShort(Location *location) {
    if (location) printf("%s\n%s\n",location->name,location->desc);
}


Stack *readFile(Game* game, char *fileName) {
    const int possible_directions = 6;
    const int max_object_per_room = 6;
    //Checks if the filename is not null
    if(!fileName) return NULL;

    Location **locationList = malloc(sizeof(Location*));
    int locationCount = 0;

    Object **objectList= malloc(sizeof(Object*));
    int objectCount = 0;

    int** locationLinks = malloc(sizeof(int*));
    int** objectLinks = malloc(sizeof(int*));


    //Opens the file
    FILE *file;
    char * line = NULL;
    size_t len = 0;
    size_t read;
    file = fopen(fileName, "r");

    //If file doesn't exists returns null
    if(!file) return NULL;

    bool readingRoom = false;
    bool readingObject = false;
    int subIndex = 0;

    while ((read = getline(&line, &len, file)) != -1) {
        //Checks if we are reading a room header
        if (strstr(line, "@room") != NULL) {
            locationCount++;
            locationList = realloc(locationList, sizeof(Location*) * locationCount);
            locationList[locationCount-1] = LocationNew(NULL, NULL);
            
            locationLinks = realloc(locationLinks, sizeof(int*) * locationCount);
            locationLinks[locationCount-1] = malloc(sizeof(int) * possible_directions);

            subIndex=0;
            readingObject = false;
            readingRoom = true;

            char *token = strtok(line, " ");
            token = strtok(NULL, " ");
            locationList[locationCount-1]->index = atoi(token);

        }
        //Checks if we are reading a object header
        else if (strstr(line, "@object") != NULL) {
            objectCount++;
            objectList = realloc(objectList, sizeof(Object*) * objectCount);
            objectList[objectCount-1] = ObjectNew(NULL, NULL);

            objectLinks = realloc(objectLinks, sizeof(int*) * objectCount);
            objectLinks[objectCount-1] = malloc(sizeof(int));
            
            subIndex=0;
            readingObject = true;
            readingRoom = false;

            char *token = strtok(line, " ");
            token = strtok(NULL, " ");
            objectList[objectCount-1]->index = atoi(token);
        }

        //If we are reading a object and not its header
        else if(readingObject) {
            switch (subIndex)
            {
                // If its the Title line
                case 0:
                    objectList[objectCount-1]->name = strndup(line, strlen(line) - 1);
                    break;
                // If its the Indexes line
                case 1:
                    objectLinks[objectCount-1][0] = atoi(line);
                    break;
                // If its the Description Line
                default:
                    //If there is no description, allocates memory for the description of size equal to the size of the line
                    if(!objectList[objectCount-1]->desc) {
                        objectList[objectCount-1]->desc = strdup(line);
                    }
                    //Concatenates the already stored description with the current line
                    else {
                        strcat(objectList[objectCount-1]->desc , strdup(line));
                    }
                    break;
            }
            subIndex++;
        }

        //If we are reading a room and not its header
        else if(readingRoom) {
            switch (subIndex)
            {
                // If its the Title line
                case 0:
                    locationList[locationCount-1]->name = strndup(line, strlen(line) - 1);
                    break;
                // If its the Index line
                case 1:
                    char *token = strtok(line, " ");
                    locationLinks[locationCount-1][0] = atoi(token); 
                    for (int i = 1; i < possible_directions ; i++) {
                        token = strtok(NULL, " ");
                        locationLinks[locationCount-1][i] = atoi(token); 
                    }
                    break;
                // If its the Description Line
                default:
                    //If there is no description, allocates memory for the description of size equal to the size of the line
                    if(!locationList[locationCount-1]->desc) {
                        locationList[locationCount-1]->desc = strdup(line);
                    }

                    //Concatenates the already stored description with the current line
                    else {
                        strcat(locationList[locationCount-1]->desc, strdup(line));
                    }
                    break;
            }
            subIndex++;
        }
    }

    Stack *locationStack = malloc(sizeof(Stack));
    for (int j = 0; j < objectCount ; j++) {
        //Removes the /n at the end of the description of the current object
        char *temp = malloc((sizeof(char*) * strlen(objectList[j]->desc)+(sizeof(char*))));
        strcpy(temp, objectList[j]->desc);
        free(objectList[j]->desc);
        objectList[j]->desc = strndup(temp, strlen(temp) - 1);
        free(temp);

        // Either adds the object to the player's invetory or to its assigned room
        if(objectLinks[j][0] == -1) {
            AddObjectToInventory(game->player, objectList[j]);
        }
        else {
            AddObjectToLocation(locationList[objectLinks[j][0]-1], objectList[j]);
        }
    }
    for (int i = locationCount-1; i >= 0 ; i--) {
        //Removes the /n at the end of the description of the current location
        char *temp = malloc((sizeof(char*) * strlen(locationList[i]->desc)+(sizeof(char*))));
        strcpy(temp, locationList[i]->desc);
        free(locationList[i]->desc);
        locationList[i]->desc = strndup(temp, strlen(temp) - 1);
        free(temp);

        //Binds the exits of a location to others in accordance to the location links list
        for (int j = 0; j < possible_directions ; j++) {
            if(locationLinks[i][j] == -1) continue;
            LocationSetExit(locationList[i], j, locationList[locationLinks[i][j]-1]);
        }
        
        locationStack = StackPush(locationStack, locationList[i]);
    }
    //Closes the file and frees the line
    fclose(file);
    if (line) free(line);
    if (locationList) free(locationList);
    if (objectList) free(objectList);
    if (locationLinks) {
        for (size_t i = 0; i < locationCount; i++)
        {
            if (locationLinks[i]) free(locationLinks[i]);
        }
        
        free(locationLinks);
    }
    if (objectLinks) {for (size_t i = 0; i < objectCount; i++)
        {
            if (objectLinks[i]) free(objectLinks[i]);
        }
        free(objectLinks);
    }
    
    return locationStack;
} 

Location *LocationInit(Game* game) {
    Stack *locationStack = readFile(game, "world.txt");
    game->locationStack = locationStack;
    return StackHead(game->locationStack);
}

void LocationDestroy(Game* game) {
    Stack * temp = game->locationStack;
    while (!StackIsEmpty(temp))
    {
        LocationDelete(StackHead(temp));
        temp = StackPop(temp);
    }
    free(game->locationStack);
}