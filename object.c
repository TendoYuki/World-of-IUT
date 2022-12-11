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

bool AddObjectToInventory(Mobile *player, Object *object) {
    for(int j=0;j<6;j++){
        if(!player->inventory[j]){
            player->inventory[j] = object;
            printf("You received a %s\n", player->inventory[j]->name);
            return true;
        }
    }
    printf("There's no more place in your inventory\n");
    return false;
}