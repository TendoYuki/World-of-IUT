#include <stdio.h> /* for printf in Intro() */
#include "game.h" /* for Game structure and GameInit() */
#include "cmd.h" /* for processCommand() */

void Intro()
{
    printf("Welcome to WorlOfIUT!\n" 
           "Be prepared because you are about to live extraordinary, frightful, yet exciting\n"
           "adventures...\n" 
           "If you're new to the game, you can start by typing 'help'\n" 
           "Farewell, and may the spirit of the Vosges be with you!\n");
}


int main(int argc, char *argv[])
{
    Intro();
    Game *g=GameInit();
    while(1) processCommand(g);
    return 0;
}
