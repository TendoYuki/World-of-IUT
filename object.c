#include "object.h"
#include "location.h"
#include "mobile.h"
#include <string.h>
#include <stdio.h>

Object *ObjectNew(char *name) {
    Object *object = (Object*)NULL;
    if (name)
    {   
        object = malloc(sizeof(Object));
        if (object) 
        {
            object->name=strdup(name);
        }
    }
    return object;
}

void ObjectDelete(Object *object) {
    if (object)
    {
        if (object->name) free(object->name);
        free(object);
    }
}

int AddObjectToInventory(Mobile *player, Object *object) {
    if(!player || !object) return -1;
    int objectIndexInLocation = -1;
    for(int j=0;j<6;j++){
        if(!player->inventory[j]){
            player->inventory[j] = object;
            objectIndexInLocation = j;
            break;
        }
    }
    return objectIndexInLocation;
}

int AddObjectToLocation(Location *location, Object *object) {
    if(!location || !object) return -1;
    int objectIndexInLocation = -1;
    for(int j=0;j<6;j++){
        if(!location->objects[j]){
            location->objects[j]= object;
            objectIndexInLocation = j;
            break;
        }
    }
    return objectIndexInLocation;
}

int ObjectIsInPlayerInventory(Mobile *player, char *objectName) {
    if(!player || !objectName) return -1;
    int indexInPlayerInventory = -1;
    for(int i = 0; i<6;i++){
        if(player->inventory[i] && !strcasecmp(player->inventory[i]->name, objectName)){
            indexInPlayerInventory = i;
            break;
        }
    }
    return indexInPlayerInventory;
}

int ObjectIsInLocation(Location *location, char *objectName) {
    if(!location || !objectName) return -1;
    int indexInLocation = -1;
    for(int j=0;j<6;j++){
        if(location->objects[j] && !strcasecmp(location->objects[j]->name, objectName)){
            indexInLocation = j;
            break;
        }
    }
    return indexInLocation;
}