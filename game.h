#ifndef GAME_H
#define GAME_H

#include "mobile.h"
#include "stack.h"

typedef struct
{
    Mobile *player;
    Stack *locationStack;
} Game;

extern Game *GameInit();
extern Game *GameShutdown(Game *g);
#endif // GAME_H
