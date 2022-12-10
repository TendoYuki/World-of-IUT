#ifndef MOBILE_H
#define MOBILE_H

typedef struct 
{
    char *name;
    char *desc;
} Mobile;

extern Mobile *MobileNew(char *name, char *desc);
extern Mobile *MobileDelete(Mobile *m);
extern void MobilePrint(Mobile *m);
#endif // MOBILE_H