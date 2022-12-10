#ifndef STACK_H
#define STACK_H
#include <stdbool.h>
#include "types.h"

extern const Stack *empty_stack;

/**
 * Verifies if the stack is empty
*/
bool StackIsEmpty(Stack *stack);

/**
 * Creates a new Stack and push it into the current stack, returns the new stack
*/
Stack *StackPush(Stack *stack, Location *location);

/**
 * Returns the location of the head of the stack 
*/
Location *StackHead(Stack *stack);

/**
 * Returns the stack without the stack head
*/
Stack *StackPop(Stack *stack);

#endif