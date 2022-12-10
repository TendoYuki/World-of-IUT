
/**
 * Location type having a name and a desctiption
 * Property Directions is a table of pointer locations, which each NULL Location represents the absence of one
 * The indexes of Directions correspond to the following
 * 0 -> North
 * 1 -> East
 * 2 -> South
 * 3 -> West
 * 4 -> Top
 * 5 -> Bottom
*/
typedef struct Location {
    char *name;
    char *desc;
    Location **Directions;
} Location;

/**
 * Creates and retruns a newly allocated location with malloc()
*/
Location *LocationNew(char *name, char *desc);

/**
 * Destroys and deallocates a location passed in parameter
*/
void LocationDelete(Location*);

/**
 * Displays in the terminal a location passed in parameter
*/
void LocationPrint(Location*);

/**
 * Displays shortly in the terminal a location passed in parameter
*/
void LocationPrintShort(Location*);

/**
 * Creates and allocates all locations available
*/
void LocationInit();

/**
 * Destroys and deallocates all locations available
*/
void LocationDestroy();