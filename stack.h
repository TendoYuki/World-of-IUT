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
 * Verify if the stack is empty
*/
bool StackIfEmpty(Stack* stack);

/**
 * Create a new Stack and push it into the current stack
*/
Stack* StackPush(Stack* stack,char* name, char* desc);

/**
 * Return the location of the head of the stack 
*/
Location* StackHead(Stack*);

#endif