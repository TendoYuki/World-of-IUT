#include "cmd.h"
#include "mobile.h" /* Mobile type for player management */
#include "object.h"
#include "exits.h" /* getDir and DIRECTION type */
#include <string.h> /* strtok, strlen */
#include <strings.h> /* strcasecmp */
#include <stdio.h> /* printf and stdin */
#include <stdlib.h> /* exit and free */

static const char prompt[]="-->";
static const char sep[]="     \n";

/* react to command "help": print the help message and return */
void cmdHelp()
{
    printf(
        "General help\n"
        "To play, just enter commands after the prompt '-->'\n"
        "Available commands are:\n"
        "- help:         to get this help\n"
        "- quit:         to quit this game\n"
        "- look <where>: to look at places, objects, etc. Use 'look around' to look at the\n"
        "                current room, 'look me' to have a look at yourselves, and\n"
        "                'look <dir>' to look in the given direction (e.g. 'look east' to\n"
        "                look east from the current room). Allowed directions are north, east,\n"
        "                south, west, up, and down.\n"
        "- go <dir>:     to go in the given direction.\n"
        "- exits:        to see all the possible exits of your current place\n"
        "- get <object>: to take an object on the current location\n"
        "- drop <object>:to drop an object you have on the current location\n"
        "- inventory:    to look a your inventory ( all the objects you have )\n"
    );
}

/* react to command "quit": properly shuts the game down using GameShutdown and exit */
void cmdQuit(Game *game)
{
	game=GameShutdown(game);
    exit(0);
}

/* 
    react to command "look". What to look is provided by args. It may be:
    - me: have a look at yourselves
    - around: look at the place you're in
    - <direction>: take a peek in the given direction
    - else just print "You look at <args>"
 */
void cmdLook(Game *game, char *args)
{
    if (!args || strlen(args)==0) 
    {
        printf("You must tell what to look (cf 'Help')\n");
        return;
    }
    Mobile *player=game->player;
    if (!strcasecmp(args,"me")) MobilePrint(player);
    else if (!strcasecmp(args,"around"))
        printf("%s\n%s\n",game->player->location->name ,game->player->location->desc);
    else if (!strcasecmp(args,"objects")) {
        printf("You look for objects.\n");
        bool objectPresent = false;
        for(int i = 0 ; i < 6 ; i++) {
            if (game->player->location->objects[i]) {
                printf("%s, %s\n", game->player->location->objects[i]->name, game->player->location->objects[i]->desc);
                objectPresent = true;
            }
        }
        if(!objectPresent) printf("You understand that there is nothing there\n");
    }
    else {
        Direction dir=strtodir(args);
        if (dir == WRONGDIR) {
            printf("You cannot look %s\n",args);
            return;
        }
        if (game->player->location->directions[dir]) printf("You look %s. You see %s\n",args, game->player->location->directions[dir]->name);
        else printf("You look %s. Nothing's there\n",args);
    }
}

void cmdLookExits(Game *game){
    char *dir_str[]={"north","east","south","west","up","down"};
    for (int i=0;i<6;i++){
        if(game->player->location->directions[i]){
            printf("If you look %s, You see %s\n",dir_str[i],game->player->location->directions[i]->name);
        }
    }
}
/* react to command "go". The direction to move in is given by args */
void cmdGo(Game *game,char *args)
{
    if (!args || strlen(args)==0) 
    {
        printf("You must provide a direction to go to (cf 'Help')\n");
        return;
    }

    Direction dir=strtodir(args);
    if (dir == WRONGDIR) printf("You cannot go %s\n",args);
    else {
        if(!game->player->location->directions[dir]) {
            printf("You cannot go %s, there's nothing there\n",args);
            return;
        }
        MobileMove(game->player, game->player->location->directions[dir]);
        LocationPrint(game->player->location);
    
        //Easter Egg
        if (strcasecmp(game->player->location->name,"Living Room") == 0) {
            if(ObjectIsInPlayerInventory(game->player, "knife") != -1) {
                printf("Unfortunately, you slipped on a banana peel, and fell,\nThe knife you took with you, accidentaly sliced your throat open.\nAlthough you were in the living roomn you died ! What a looser !\n");
                cmdQuit(game);
            }
        }
        if (strcasecmp(game->player->location->name,"Attic")==0){
            if(ObjectIsInPlayerInventory(game->player, "bread loaf") != -1) {
                printf("Unfortunately, you had bread on you and some starving rats just attacked you\nAnd you died from a rare desease\nMaybe you will be luckier in your next life\n");
                cmdQuit(game);
            }
        }
    }
}


void cmdInventory(Game *game){
    bool hasItem = false;
    for (int i=0;i<6;i++){
        if(game->player->inventory[i]) {
            printf("You have a %s\n",game->player->inventory[i]->name);
            hasItem = true;
        }
    }
    if(!hasItem) printf("You have nothing in your inventory\n");
}

void cmdGet(Game *game,char *args){
    if (!args || strlen(args)==0) 
    {
        printf("You must provide an object to take (cf 'Help')\n");
        return;
    }
    int indexInLocation = ObjectIsInLocation(game->player->location, args);
    if(indexInLocation!=-1) {
        if (AddObjectToInventory(game->player, game->player->location->objects[indexInLocation])) game->player->location->objects[indexInLocation] = NULL;
        return;
    }
    printf("This object isn't here\n");
}

void cmdDrop(Game *game,char *args){
    if (!args || strlen(args)==0) 
    {
        printf("You must provide an object to drop (cf 'Help')\n");
        return;
    }
    int indexPlayerInventory = ObjectIsInPlayerInventory(game->player, args);
    if(indexPlayerInventory != -1) {
        for(int j=0;j<6;j++){
            if(!game->player->location->objects[j]){
                game->player->location->objects[j]= game->player->inventory[indexPlayerInventory];
                game->player->inventory[indexPlayerInventory] = NULL;
                printf("You dropped a %s\n", game->player->location->objects[j]->name);
                return;
            }
        }
        printf("There's no more place in this room\n");
        return;
    }
    printf("You don't have this object\n");
}

/* 
    read a line from standard input and return it. 
    The returned string was allocated using malloc and free must be called for deallocation 
*/
char *getInput()
{
    char *line=NULL;
    size_t linecap=0;
    printf("%s ",prompt); /* print the prompt before reading the line */
    getline(&line,&linecap,stdin); /* allocates line, which will have to be freed */
    return line;
}

/* 
    parse the input line in two words: the first word is the command and the second is the argument
    line and game must be non-null pointers for anything to happen 
*/
void parseAndExecute(char *line, Game *game)
{
    if (line && game) /* check pointers validity */
    {   
        char *lineCpy = strdup(line);      
        char *name=strtok(line,sep); /* extract first word = command */
        if (name) // null pointer if line just contains a return (empty line)
        {
            char *args=strtok(NULL,sep); /* extract the second word = argument. The rest of the line is disregarded */
            /* call the appropriate function, depending on the command */
            if (!strcasecmp(name,"help")) cmdHelp(); /* cmd=="help" -> call cmdHelp() */
            else if (!strcasecmp(name,"quit")) cmdQuit(game); /* cmd=="quit" -> call cmdQuit(). Also properly shuts the game down */
            else if (!strcasecmp(name,"look")) cmdLook(game,args); /* cmd=="look" -> call cmdLook(). args specify where/what to look. game contains the necessary info about stuff to look at */
            else if (!strcasecmp(name,"go")) cmdGo(game,args); /* cmd="go" -> call cmdGo(). args specify where to go. game contains info about locations and will update the player's location */
            else if (!strcasecmp(name,"exits")) cmdLookExits(game);
            else if (!strcasecmp(name,"get")) {
                char *unparesdArgs = strndup(strchr(lineCpy, ' ') + 1, strlen(strchr(lineCpy, ' ') + 1) - 1); // Manipluation necessary to get argument with spaces
                cmdGet(game,unparesdArgs);
                free(unparesdArgs);
                free(lineCpy);
            } 
            else if (!strcasecmp(name,"drop")) {
                char *unparesdArgs = strndup(strchr(lineCpy, ' ') + 1, strlen(strchr(lineCpy, ' ') + 1) - 1); // Manipluation necessary to get argument with spaces
                cmdDrop(game,unparesdArgs);
                free(unparesdArgs);
                free(lineCpy);
            }
            else if (!strcasecmp(name,"inventory")) cmdInventory(game);
            else printf("Command not found. Try 'help'\n");
        }
        else printf("Command not found. Try 'help'\n");
    }
}

/* reads a user input command line and process to progress in the game */
void processCommand(Game *g)
{
    char *s=getInput(); /* reads a user input line */
    parseAndExecute(s,g); /* process it, and move in the game */
    if (s) free(s); /* deallocate the string from getInput() */
}
