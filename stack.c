#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * 
*/
const Stack *empty_stack = (Stack*)NULL;

bool StackIsEmpty(Stack *stack){
    return stack==empty_stack;
}

Stack *StackPush(Stack *stack, Location *location){
    Stack* new = malloc(sizeof(Stack));
    if(!new) return NULL;
    if (stack && location){
        new->location = location;
        new->next = stack;
        return new;
    }
    free(new);
    return NULL;
}

Location *StackHead(Stack *stack){
    return stack->location;
}

Stack *StackPop(Stack *stack){
    return stack->next;
}