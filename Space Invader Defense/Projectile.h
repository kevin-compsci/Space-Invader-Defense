//Kevin Nguyen
//kdn433

#include <ncurses.h>    // the ncurses library
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <unistd.h> // sleep
#include <iostream>
#include <string>
#include <list>

using namespace std;

//Projectile derived from GameObject
class Projectile : public GameObject {
public:

	//Declarations
	int projX; int projY;

	//Constructors	
	Projectile() {};
	
	Projectile(int x, int y) {
		projX = x;
		projY = y;
	};
	
	//player projectile
	bool PlayerFire() {
		if (projY > 3) {
			mvprintw(projY--, projX, "|");
		}
		
		if (projY <= 3) {
			return true;
		}
		return false;
	};
	
	//enemy projectile
	bool EnemyFire() {
		if (projX < 30) {
			mvprintw(projX++, projY, "|");
		}
		
		if (projX >= 30) {
			return true;
		}
		return false;	
	};

	//player projectile hits the enemy
	bool playerHitEnemy(int eX, int eY, int projectileX, int projectileY) {		
		if ((eX == projectileX) && (eY == projectileY)) {
			return true;	
		}
		return false;
	};

};
