#ifndef STACK_H
#define STACK_H
#include <stdbool.h>
#include "location.h" 
typedef struct Stack
{
    Location* location;
    Stack* next;
}Stack;

extern const empty_stack;

/**
 * Verifies if the stack is empty
*/
bool StackIsEmpty(Stack* stack);

/**
 * Creates a new Stack and push it into the current stack
*/
Stack* StackPush(Stack* stack,char* name, char* desc);

/**
 * Returns the location of the head of the stack 
*/
Location* StackHead(Stack* stack);

/**
 * Returns the stack without the stack head
*/
Stack* StackPop(Stack* stack);

#endif