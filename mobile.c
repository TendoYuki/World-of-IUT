#include "mobile.h"
#include <string.h> /* strdup */
#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */

Mobile *MobileNew(char *name, char *desc)
{
    Mobile *ret=(Mobile*)NULL;
    if (name && desc)/** && where)**/
    {
        ret=malloc(sizeof(Mobile));
        ret->name=strdup(name);
        ret->desc=strdup(desc);
    }
    return ret;
}

Mobile *MobileDelete(Mobile *m)
{
    if (m)
    {
        if (m->name) free(m->name);
        if (m->desc) free(m->desc);
        free(m);
    }
    return (Mobile *)NULL;
}

void MobilePrint(Mobile *m)
{
    if (m) printf("%s\n%s\n",m->name,m->desc);
}

void *MobileMove(Mobile *m, Location *location) {
    if(location && m) m->location = location;
}