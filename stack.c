#include "stack.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * 
*/
extern const empty_stack = (Stack*)NULL;

bool StackIsEmpty(Stack* stack){
    return stack==empty_stack;
}

Stack* StackPush(Stack* stack, char* name, char* desc){
    Stack* new = malloc(sizeof(Stack));
    if(!new) return NULL;
    if (stack && name && desc){
        new->location = LocationNew(name,desc);
        new->next = stack;
        return new;
    }
    free(new);
    return NULL;
}