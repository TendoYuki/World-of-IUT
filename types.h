#ifndef TYPES_H
#define TYPES_H

typedef struct Object{
    char *name;
    char *desc;
    int index;
}Object;

typedef struct Location {
    char *name;
    char *desc;
    int index;
    struct Location **directions;
    Object **objects;
} Location;

typedef struct Mobile
{
    char *name;
    char *desc;
    Location *location;
    Object **inventory;
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