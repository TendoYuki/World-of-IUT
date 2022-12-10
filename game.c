#include "game.h"
#include "mobile.h"
#include "location.h"
#include <stdlib.h> /* malloc, free, NULL */

/* Initialize everything that makes up the game: player and locations */
Game *GameInit()
{
    Game *ret=malloc(sizeof(Game));
    if(ret)
    {
        ret->player = MobileNew("You", "A very dynamic and adventurous young person!");
        MobileMove(ret->player,LocationInit());
    }
    return ret;
}

/* correctly deallocate everythig that was dynamically allocated in GameInit */
Game *GameShutdown(Game *g)
{
    if (g)
    {
        g->player=MobileDelete(g->player);
        LocationDestroy(g);
        free(g);
    }
    return (Game*)NULL;
}