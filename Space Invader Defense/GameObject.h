//Kevin Nguyen
//kdn433


//#include <ncurses.h>    // the ncurses library
#include <stdlib.h>     /* srand, rand */
//#include <time.h>       /* time */
#include <unistd.h> // sleep
#include <iostream>
#include <string>

using namespace std;

//Game Object class
class GameObject {
public:
	//Declarations
	int projEX, projEY, sX, sY;
	
	//gets borders and prints them out for game
	virtual void getBorders(int x, int y) {
		//mvprintw(x,y,"$\n"); //border?
		for (int i = 3; i < 30; i++) {
			for (int j = 3; j < 40; j++) {
				if ((i == 3) || (i == 29)) {
					mvprintw(i,j,"#"); //border?
				}
				else if (((j == 3) || (j == 39)) && ((i >= 3) && (i <= 29))) {
					mvprintw(i,j,"#"); //border?

				}
			}
		}
	};
	
	//checks collision based on coordinates
	virtual bool isCollision(int projEnemyX, int projEnemyY, int shipX, int shipY) {
		projEX = projEnemyX, projEY = projEnemyY, sX = shipX+27, sY = shipY+1;
		if ((projEX == sX) && (projEY == sY)) {
			return true;
		}
		return false;
	};
};

