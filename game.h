#ifndef GAME_H
#define GAME_H

#include "mobile.h"

typedef struct
{
    Mobile *player;
} Game;

extern Game *GameInit();
extern Game *GameShutdown(Game *g);
#endif // GAME_H
