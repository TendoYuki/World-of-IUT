#include "location.h"
#include "exits.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "stack.h"

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


Stack *readFile(char *fileName) {
    const int possible_directions = 6;
    //Checks if the filename is not null
    if(!fileName) return NULL;

    Location **locationList = malloc(sizeof(Location*));
    int locationCount = 0;

    int** links = malloc(sizeof(int*));

    int objectCount = 0;

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
            locationList[locationCount-1] = malloc(sizeof(Location));
            locationList[locationCount-1]->directions = malloc(sizeof(Location*) * possible_directions);

            links = realloc(links, sizeof(int*) * locationCount);

            links[locationCount-1] = malloc(sizeof(int) * possible_directions);

            subIndex=0;
            readingObject = false;
            readingRoom = true;

            char *token = strtok(line, " ");
            token = strtok(NULL, " ");
            locationList[locationCount-1]->index = atoi(token);

        }
        //Checks if we are reading a object header
        else if (strstr(line, "@object") != NULL) {
            printf("\n");
            subIndex=0;
            readingObject = true;
            readingRoom = false;
            

            // line = strtok(line, " ");
            // printf("Object number : %s", strtok(NULL, " "));
        }

        //If we are reading a object and not its header
        else if(readingObject) {
            switch (subIndex)
            {
                // If its the Title line
                case 0:
                    printf("title : %s", line);
                    break;
                // If its the Indexes line
                case 1:
                    printf("index : %s", line);
                    break;
                // If its the Description Line
                case 2:
                    printf("%s", line);
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
                    locationList[locationCount-1]->name = malloc(sizeof(char*) * (strlen(line) + 1));
                    strcpy(locationList[locationCount-1]->name, line);
                    break;
                // If its the Index line
                case 1:
                    char *token = strtok(line, " ");
                    links[locationCount-1][0] = atoi(token); 
                    for (int i = 1; i < possible_directions ; i++) {
                        token = strtok(NULL, " ");
                        links[locationCount-1][i] = atoi(token); 
                    }
                    // locationList[locationCount-1]->directions = atoi(line);//
                    break;
                // If its the Description Line
                default:
                    //If there is no description, allocates memory for the description of size equal to the size of the line
                    if(!locationList[locationCount-1]->desc) {
                        locationList[locationCount-1]->desc = malloc(sizeof(char*) * (strlen(line) + 1));
                        strcpy(locationList[locationCount-1]->desc, line);
                    }

                    /*
                    If there is already a description, meaning that we are reading a multi line description
                    We are going to create a variable cpy of the size of the already stored description to which will be added the size of the current line
                    We are then going to copy the already stored description in the cpy variable And concatenate it with the current line
                    Then we are going to reallocate the already stored description to its size plus the size of the current line  
                    And finally we will copy the temp variable into the description and freeing the copy

                    TL;DR Concatenates the already stored description with the current line
                    */
                    else {
                        char *cpy = malloc((sizeof(char*) * strlen(locationList[locationCount-1]->desc)+(sizeof(char*) * (strlen(line) + 1))));
                        strcpy(cpy, locationList[locationCount-1]->desc);
                        strcat(cpy, line);
                        locationList[locationCount-1]->desc = realloc(locationList[locationCount-1]->desc, (sizeof(char*) * strlen(locationList[locationCount-1]->desc)+(sizeof(char*) * (strlen(line) + 1))));
                        strcpy(locationList[locationCount-1]->desc, cpy);
                        free(cpy);
                    }
                    break;
            }
            subIndex++;
        }
    }

    Stack *locationStack;

    for (int i = locationCount-1; i >= 0 ; i--) {
        for (int j = 0; j < possible_directions ; j++) {
            if(links[i][j] == -1) continue;
            LocationSetExit(locationList[i], j, locationList[links[i][j]-1]);
        }
        locationStack = StackPush(locationStack, locationList[i]);
    }
    //Closes the file and frees the line
    fclose(file);
    if (line) free(line);
    return locationStack;
} 

Location *LocationInit() {
    Stack *locationStack = readFile("world.txt");
    return StackHead(locationStack);
}

void LocationDestroy(Game* game) {
    Stack * temp = game->locationStack;
    while (!StackIsEmpty(temp))
    {
        LocationDelete(StackHead(temp));
        temp = StackPop(temp);
    }
}