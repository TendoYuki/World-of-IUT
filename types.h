#ifndef TYPES_H
#define TYPES_H

/**
 * Object type containing a name a descitption and an unique index.
*/
typedef struct Object{
    char *name;
    char *desc;
    int index;
}Object;

/**
 * Location type containing a name a description and unique index a List of pointer to possible exits and a list of contained objects  
*/
typedef struct Location {
    char *name;
    char *desc;
    int index;
    struct Location **directions;
    Object **objects;
} Location;

/**
 * Mobile type containing a name a description, its current location and his inventory (List of pointer to objects)
*/
typedef struct Mobile
{
    char *name;
    char *desc;
    Location *location;
    Object **inventory;
} Mobile;

/**
 * Stack type containing a location and a pointer to the next element in the stack
*/
typedef struct Stack
{
    Location* location;
    struct Stack* next;
}Stack;

/**
 * Game type containing a reference to the player and to the location stack
*/
typedef struct Game
{
    Mobile *player;
    Stack *locationStack;
} Game;

#endif