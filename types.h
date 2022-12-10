#ifndef TYPES_H
#define TYPES_H

typedef struct Location {
    char *name;
    char *desc;
    int index;
    struct Location **directions;
    
} Location;

typedef struct Mobile
{
    char *name;
    char *desc;
    Location *location;
} Mobile;

typedef struct Stack
{
    Location* location;
    struct Stack* next;
}Stack;

typedef struct Game
{
    Mobile *player;
    Stack *locationStack;
} Game;

#endif