#include "exits.h"
#include <strings.h> /* strcasecmp */
#include <stddef.h> /* NULL */

static char *dir_str[]={"north","east","south","west","up","down"};

Direction strtodir(char *name)
{
    for (int i=NORTH; i<=DOWN; i++)
        if (!strcasecmp(name,dir_str[i])) return i;
    return WRONGDIR;
}

char *dirtostr(Direction d)
{
    if (d >= NORTH && d <= DOWN) return dir_str[d];
    return (char *)NULL;
}