/** 
Name: Kevin Nguyen
Eid: kdn433
*/

//includes that are needed for game
#include <ncurses.h>    // the ncurses library
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <unistd.h> 	// sleep
#include <list>
#include "timehelper.h"
#include "GameObject.h"
#include "Projectile.h"
#include "Ship.h"
#include "EnemyShip.h"
#include "PlayerShip.h"

//main function
int main (int argc, char const *argv[])
{
	bool tryAgain = true;
	while (tryAgain) {
    srand (time(NULL)); /// seed to some random number based on time
    if ( initscr() == NULL ) { /// init the screen, defaults to stdscr
        fprintf(stderr, "Error initialising ncurses.\n");
        exit(EXIT_FAILURE);
    }

    noecho(); /// don't echo keypresses
    keypad(stdscr, TRUE); /// set the keypad to stdscr
    nodelay(stdscr, false);
    curs_set(0); /// set cursor to invisible (if allowed by the os)
    const int delay = 50; /// milliseconds
    timeout(delay); /// set how long between keypresses (more or less)

	//Declarations
	char answer;
    	int ch = 0;
	int ammo = 50;
    	int points = 0;
    	int x = 3;
    	int y = 3;
    	int elapsedTime = getElapsedTime();
	int xTemp = 0;
	int yTemp = 0;
	int enemyCounter = 3;
	int tickCount = 0;
	int epTick = 0;
	int epTick2 = 0;
	int testtime;
	int eProjX, eProjX2;
	int eProjY, eProjY2;
	
	bool shiftDown = false;
	bool shiftDown2 = false;
	bool shiftedAlready = false;
	bool shiftedAlready2 = false;
	bool atCeiling = false;
	bool atEnemy = false;
	bool atGround = false;
	bool directionRight = false;
	bool directionRight2 = false;
	bool quit = false;
	bool won = false;
	
	list<Projectile> enemyProjectile;
	list<Projectile> enemyProjectile2;
	list<Projectile> projectileList;
	list<EnemyShip> enemyList;
	list<EnemyShip> enemyList2;
	GameObject j;
	Projectile p;
	Projectile ep;
	EnemyShip e;
	EnemyShip e2;
	PlayerShip s;
	start_color();

	//ship w into object list
	while (enemyCounter < 30) {
		e = EnemyShip(4,5+enemyCounter);
		enemyList.push_back(e);
		enemyCounter = enemyCounter + 2;
	}
	enemyCounter = 3;

	//ship u into object list
	while (enemyCounter < 30) {
		e2 = EnemyShip(5,5+enemyCounter);
		enemyList2.push_back(e2);
		enemyCounter = enemyCounter + 2;
	}

	//game loop and beginning	
    	while (!quit){
	//game title
	mvprintw(2,10, "SPACE INVADER DEFENSE");

	//Game rules
	mvprintw(3, 50, "GAME RULES");
	mvprintw(4, 50, "__________");
	mvprintw(7, 45, "1.) There are two enemy formations: W-enemy-motherhips and u-enemy ships");
	mvprintw(8, 45, "W enemy-mother ships can cause all enemy ships to move down by one!");
	mvprintw(9, 45, "u enemy ships does not cause all ships to move down by one!");
	mvprintw(11, 45, "2.) Use arrow keys to move your ship! Press spacebar to fire your laser!");
	mvprintw(12, 45, "Destroy all enemy ships to win! Remember your ammo is limited!");
	mvprintw(14, 45, "3.) You lose if you get shot down or the enemy invasion lands!");
	mvprintw(16, 45, "GOOD LUCK!");
	
	//Color to the game border and prints borders
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	attron(COLOR_PAIR(1));
	j.getBorders(x,y);
	attroff(COLOR_PAIR(1));

        ch = getch();
        erase(); /// erase the screen (after getch())
        if ( ch != ERR) { /// user has a keypress
            /// this is to delay until the next tick
            elapsedTime = getElapsedTime();
            if (elapsedTime < delay) {
                nsleep(delay-elapsedTime);}
        }
	
	//color for enemy ships and logic
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	attron(COLOR_PAIR(2));
	//obtains enemyShip W to display on window
	for (list<EnemyShip>::iterator iterateEShip = enemyList.begin(); iterateEShip != enemyList.end(); iterateEShip++) {
		(*iterateEShip).getEnemyShipW();
	}
	
	//obtains enemyShip u to display on window
	for (list<EnemyShip>::iterator iterateEShip2 = enemyList2.begin(); iterateEShip2 != enemyList2.end(); iterateEShip2++) {
		(*iterateEShip2).getEnemyShipU();
	}

	if (tickCount >= 20) {
		//move the enemy ships
		for (list<EnemyShip>::iterator iterate = enemyList.begin(); iterate != enemyList.end(); iterate++) {
			if ((*iterate).checkLeftPos(4) && !shiftedAlready) {
				directionRight = true;
				shiftDown = true;
			}

			if (shiftDown) {
				for (list<EnemyShip>::iterator iterate2 = enemyList.begin(); iterate2 != enemyList.end(); iterate2++) {
					(*iterate2).xPosE++;
				}
				shiftDown2 = true;
				shiftDown = false;
				shiftedAlready = true;
				break;
			}
			else {
				shiftedAlready = false;
			}	
			(*iterate).moveEShipW(3, 38, directionRight);
			quit = (*iterate).enemyLanded();

			if ((*iterate).checkRightPos(38)) {
				directionRight = false;
				shiftDown = true;
				break;
			}		
		}
		//move the enemy ships
		for (list<EnemyShip>::iterator iterate = enemyList2.begin(); iterate != enemyList2.end(); iterate++) {
			if ((*iterate).checkLeftPos(4) && !shiftedAlready2) {
				directionRight2 = true;
				shiftDown2 = true;
			}

			if (shiftDown2) {
				for (list<EnemyShip>::iterator iterate2 = enemyList2.begin(); iterate2 != enemyList2.end(); iterate2++) {
					(*iterate2).xPosE++;
				}
				shiftDown2 = false;
				shiftedAlready2 = true;
				break;
			}
			else {
				shiftedAlready2 = false;
			}	

			(*iterate).moveEShipU(3, 38, directionRight2);
			quit = (*iterate).enemyLanded();

			if ((*iterate).checkRightPos(38)) {
				directionRight2 = false;
				shiftDown2 = true;	
				break;
			}		
		}
		tickCount = 0;
	}
	else {
		tickCount++;
	}
	attroff(COLOR_PAIR(2));
	
	//color for enemy projectiles and logic
	init_pair(3, COLOR_RED, COLOR_BLACK);
	attron(COLOR_PAIR(3));
	srand(time(NULL));
	for (list<EnemyShip>::iterator it = enemyList.begin(); it != enemyList.end(); it++) {	
		testtime = rand() % 100 + 1;
		if (testtime <= 15) {
			eProjX = (*it).xPosE+1;
			eProjY = (*it).yPosE;
			ep = Projectile(eProjX, eProjY);
			enemyProjectile.push_back(ep);
		}
	}
	for (list<EnemyShip>::iterator it2 = enemyList2.begin(); it2 != enemyList2.end(); it2++) {	
		testtime = rand() % 100 + 1;
		if (testtime <= 8) {
			eProjX2 = (*it2).xPosE+1;
			eProjY2 = (*it2).yPosE;
			ep = Projectile(eProjX2, eProjY2);
			enemyProjectile.push_back(ep);
		}
	}
	
	if (!enemyProjectile.empty() && epTick >= 2) {
		for (list<Projectile>::iterator itEP = enemyProjectile.begin(); itEP != enemyProjectile.end(); itEP++) {
			if (epTick >= 2) {
				atGround = (*itEP).EnemyFire();
				if (atGround) {
					quit = j.isCollision((*itEP).projX, (*itEP).projY, y, x); 
					enemyProjectile.erase(enemyProjectile.begin()); itEP--;
				}
				epTick = 0;
			}
			else {
				(*itEP).projX = eProjX;
			}		
		}
	}
	epTick++;

	if (!enemyProjectile2.empty() && epTick2 >= 2) {
		for (list<Projectile>::iterator itEP = enemyProjectile2.begin(); itEP != enemyProjectile2.end(); itEP++) {
			if (epTick >= 2) {
				atGround = (*itEP).EnemyFire();
				if (atGround) {
					quit = j.isCollision((*itEP).projX, (*itEP).projY, y, x); 
					enemyProjectile2.erase(enemyProjectile2.begin()); itEP--;
				}
				epTick2 = 0;
			}
			else {
				(*itEP).projX = eProjX2;
			}		
		}
	}
	epTick2++;
	attroff(COLOR_PAIR(3));

	//Information within game
        mvprintw(0, 0, "Points: %i.   'q' to quit.\n", points);
	mvprintw(30, 13, "Ammo remaining: %i", ammo);

        /// some example code to show how to work with the keyboard
        switch(ch){
                //case KEY_UP: y--; break;
		//case KEY_DOWN: y++; break;
                
		case KEY_RIGHT:
			if (x < 37) {
				x++;
			}
			else if (x >= 38) {
				x--;
			} 
			break;               
                case KEY_LEFT:
			if (x > 3) {
				x--;
			}
			else if (x <= 1) {
				x++;
			} 
			break;

                case ' ':
			if (ammo > 0) {
				xTemp = x+1;
				yTemp = y+25;
				p = Projectile(xTemp, yTemp);
				projectileList.push_back(p);
				ammo = ammo - 1;
			}
			break;
                case 'q': 
                    quit = true;
                    break;
        }	
	
	//color for player projectile
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	attron(COLOR_PAIR(4));	
	//player projectile
	if (!projectileList.empty()) {
		for (list<Projectile>::iterator it = projectileList.begin(); it != projectileList.end(); it++) {
			atCeiling = (*it).PlayerFire();
			if (atCeiling) {
				projectileList.erase(projectileList.begin()); it--;
			}
		
			//checks if hits enemy ship u
			for (list<EnemyShip>::iterator iterate = enemyList2.begin(); iterate != enemyList2.end(); iterate++) {
				atEnemy = (*it).playerHitEnemy((*iterate).xPosE, (*iterate).yPosE, (*it).projY, (*it).projX);
				if (atEnemy) {
					points++;
					enemyList2.erase(iterate); iterate--;
					projectileList.erase(projectileList.begin()); it--;
				}
			}

			//checks if hits enemy ship W
			for (list<EnemyShip>::iterator iterate = enemyList.begin(); iterate != enemyList.end(); iterate++) {
				atEnemy = (*it).playerHitEnemy((*iterate).xPosE, (*iterate).yPosE, (*it).projY, (*it).projX);
				if (atEnemy) {
					points = points + 2;
					enemyList.erase(iterate); iterate--;
					projectileList.erase(projectileList.begin()); it--;
				}
			}
		}
	}
	attroff(COLOR_PAIR(4));
	
	//color for player ship
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	attron(COLOR_PAIR(5));

	//player ship
	s.getPlayerShip(y+25, x+1);        	
	attroff(COLOR_PAIR(5));
	
	//Checks if all ships have been destroyed, if yes then player wins and quit, else continue	
	if (enemyList.empty() && enemyList2.empty()) {
		won = true; quit = true;
	}
		
        refresh(); // refresh the screen after adding everything
        move(0,0); /// move cursor to 0,0 (looks prettier if os doesn't allow invisible cursors)
    }
    endwin();   /// cleanup the window
	//victory or loss messages
    	if (quit && !won) {
		cout << endl << "YOU LOSE! Total Score: " << points << endl;
	}
	else if (quit && won) {
		cout << endl << "YOU WIN! Total Score: " << points << endl;
	}

	//Retry message and logic
	cout << "TRY AGAIN? (Y): ";
	cin >> answer; cout << endl;	
	if ((answer == 'y') || (answer == 'Y')) {
		tryAgain = true; quit = false;
	}
	else {
		tryAgain = false; quit = true;
	}
	}
	return 0;
}