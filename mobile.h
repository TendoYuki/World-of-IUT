#ifndef MOBILE_H
#define MOBILE_H
#include "location.h"

extern Mobile *MobileNew(char *name, char *desc);
extern Mobile *MobileDelete(Mobile *m);
extern void *MobileMove(Mobile *m, Location *location);
extern void MobilePrint(Mobile *m);
#endif // MOBILE_H