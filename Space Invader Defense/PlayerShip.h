//Kevin Nguyen
//kdn433

#include <ncurses.h>    // the ncurses library
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <unistd.h> // sleep
#include <iostream>
#include <string>

using namespace std;

//PlayerShip derived from ship
class PlayerShip : public Ship {
public:
	//constructor
	PlayerShip() {};

	//Gets the player ship to the screen
	virtual void getPlayerShip(int x, int y) {
		player = '^';
		mvaddch(x, y, player); // example print a char to the screen at the y, x location
	}
};