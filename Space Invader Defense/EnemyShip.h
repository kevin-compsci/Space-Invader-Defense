//Kevin Nguyen
//kdn433

#include <ncurses.h>    // the ncurses library
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <unistd.h> // sleep
#include <iostream>
#include <string>

using namespace std;

//EnemyShip derived from ship
class EnemyShip : public Ship {
public:
	//Declarations
	int xPosE, yPosE;
	
	//Constructors
	EnemyShip() {};

	EnemyShip(int x, int y) {
		xPosE = x;
		yPosE = y;
	};

	//produces enemy ships W at given positions
	virtual void getEnemyShipW() {
		wEnemy = 'W';
		uEnemy = 'u';
		mvaddch(xPosE, yPosE, wEnemy);
	}
	
	//produces enemy ships u at given positions
	virtual void getEnemyShipU() {
		uEnemy = 'u';
		wEnemy = 'W';
		mvaddch(xPosE, yPosE, uEnemy);
	}
	

	//checks if enemy ship is at right border
	virtual bool checkRightPos(int rightLimit) {
		if (yPosE >= rightLimit) {
			return true;	
		}
		return false;
	}

	//checks if enemy ship is at left border
	virtual bool checkLeftPos(int leftLimit) {
		if (yPosE <= leftLimit) {
			return true;	
		}
		return false;
	}
	
	//moves the enemy W ship
	virtual void moveEShipW(int leftLimit, int rightLimit, bool directionRight) {
		wEnemy = 'W';
		if (directionRight == true) {
			mvaddch(xPosE, yPosE++, wEnemy);
		}
		else if(directionRight == false) {
			mvaddch(xPosE, yPosE--, wEnemy);	
		}
	}

	//moves the enemy u ship
	virtual void moveEShipU(int leftLimit, int rightLimit, bool directionRight) {
		uEnemy = 'u';	
		if (directionRight == true) {
			mvaddch(xPosE, yPosE++, uEnemy);
		}
		else if(directionRight == false) {
			mvaddch(xPosE, yPosE--, uEnemy);	
		}
	}

	//checks if enemy position is at bottom, then quit and player loses
	virtual bool enemyLanded() {
		if (xPosE >= 28) {
			return true;
		}
		return false;
	}
};