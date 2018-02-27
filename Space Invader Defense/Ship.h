//Kevin Nguyen
//kdn433

#include <ncurses.h>    // the ncurses library
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <unistd.h> // sleep
#include <iostream>
#include <string>

using namespace std;

//Ship derived from GameObject
class Ship : public GameObject {
public:
	//Declarations
	char uEnemy;
	char wEnemy;
	char player;		
};