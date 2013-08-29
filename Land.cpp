#include "stdafx.h"
#include "Land.h"
#include "Player.h"
#include "Shot.h"
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <ctime>

using namespace std;

	void Land::drawSpace() {
		cout << " ";
	}

	void Land::drawLand() {
		cout << "T";
	}

	void Land::drawPlayer() {
		cout << "@";
	}

	void Land::drawDeadPlayer() {
		cout << "X";
	}

	void Land::drawBullet() {
		cout << "*";
	}

	void Land::drawPlayerNum(int playerNum) {
		cout << playerNum;
	}

	int Land::getYForX(int x) {
		int y = map[x];
		return y;
	}

	void Land::setPlayers(Player *p) {
		players = p;
	}

	void Land::setCurrentPlayer(int currentPlayer) {
		this -> currentPlayer = currentPlayer;
	}

	void Land::setMap() {
		map = new int [maxWidth];
		int mapSize = sizeof(map)/sizeof(int);
		for (int i = 0; i < maxWidth; i++) {
			if (i==0){
				//maxheight/4 to leave room for shooting above
				int tmpHeight = rand() % (maxHeight/4) + 1;
				map[i] = tmpHeight;
			}else{
				int rnd = rand() % 3 -1;
				int previousHeight = map[i-1];
				switch (rnd) {
					case 1:
						if(previousHeight >= maxHeight) {
							map[i] = maxHeight;
						}else{
							map[i] = previousHeight+1;
						}
						break;
					case -1:
						if(previousHeight <= 1) {
							map[i] = 1;
						}else{
							map[i] = previousHeight-1;
						}
						break;
					case 0:
						map[i] = previousHeight;
						break;
				}
			}
		}
	}

	int Land::isPlayerSpace(int i, int j) {
		for (int p = 0; p < numPlayers; p++ ) {
			//if the current X occupies a player position (3 spots) and Same in the Y
			if (j >= players[p].getPos() && j < players[p].getPos()+playerWidth) {
				int baseHeight = players[p].getPos();
				int playerNum = players[p].getPlayerNum();
				if ( i <= map[baseHeight]+playerHeight && i > map[baseHeight] ) {
						return playerNum;
				}
			}
		}
		return false;
	}

	void Land::drawMap() {
		//increase bounds of height to make iot look better
		for (int i = (maxHeight*2); i > -4; i--) {
			for(int j = 0; j < maxWidth; j++) {
					// if the height at the current column = the current height we are checking
					if(map[j] >= i) {
						//if this is where a player is
						if (isPlayerSpace(i,j)) {
							//get player num
							int playerNum = isPlayerSpace(i,j);
							int playerX = players[playerNum-1].getPos();
							int playerY = players[playerNum-1].getYPos();
							if (players[playerNum-1].isAlive()) {
								if (j >= playerX && j < playerX+playerWidth && i == playerY) {
									drawPlayerNum(playerNum); //middle
								}else{
									drawPlayer();
								}
							}else{
								drawDeadPlayer();
							}
						}else{
							drawLand();
						}
					}else{
						if (isPlayerSpace(i,j)) {
							int playerNum = isPlayerSpace(i,j);
							int playerX = players[playerNum-1].getPos();
							int playerY = players[playerNum-1].getYPos();
							if (players[playerNum-1].isAlive()) {
								if (j >= playerX && j < playerX+playerWidth && i == playerY) {
									drawPlayerNum(playerNum); //middle
								}else{
									drawPlayer();
								}
							}else{
								drawDeadPlayer();
							}
						}else{
							drawSpace();
						}
					}
			}
			cout << endl;
		}
	}

	int Land::predictHit(Shot s) {
		int shotInitialY = s.y;
		int bulletDirection = s.getDirection();
		for (int i = (maxHeight*2); i > -4; i--) {
			for(int j = 0; j < maxWidth; j++) {
				shotInitialY  = s.getYForX(j,gravity);
				if (i == shotInitialY) {
					if(map[j] >= i && ((bulletDirection == 1 && j >= s.x) || (bulletDirection == -1 && j <= s.x))) {
						//hit terrain
						return -3;
					}else
					if (isPlayerSpace(i,j)) {
						//hit player
						if ((bulletDirection == 1 && j >= s.x) || (bulletDirection == -1 && j <= s.x)) {
							int playerNum = isPlayerSpace(i,j);
							if (players[playerNum-1].isAlive() && playerNum != currentPlayer) {
								//reduce health
								int health = players[playerNum-1].getHealth();
								players[playerNum-1].setHealth(health-1);
								//if that shot killed the player
								return playerNum;
							}
						}
					}
				}
			}
		}
		return -2;
	}

	void Land::drawMap(Shot s) {
		int pointOfImpact = predictHit(s);
		int bulletDirection = s.getDirection();
		//increase bounds of height to make iot look better
		int shotInitialY = s.y;
		
		cout << "HIT: " << pointOfImpact;

		for (int i = (maxHeight*2); i > -4; i--) {
			for(int j = 0; j < maxWidth; j++) {
					shotInitialY  = s.getYForX(j,gravity);
					if(map[j] >= i) {
						if (isPlayerSpace(i,j)) {
							int playerNum = isPlayerSpace(i,j);
							int playerX = players[playerNum-1].getPos();
							int playerY = players[playerNum-1].getYPos();
							if (players[playerNum-1].isAlive()) {
								if (j >= playerX && j < playerX+playerWidth && i == playerY) {
									drawPlayerNum(playerNum); //middle
								}else{
									drawPlayer();
								}
							}else{
								drawDeadPlayer();
							}
						}else{
							drawLand();
						}
					}else{
						if (isPlayerSpace(i,j)) {
								int playerNum = isPlayerSpace(i,j);
								int playerX = players[playerNum-1].getPos();
								int playerY = players[playerNum-1].getYPos();
								if (players[playerNum-1].isAlive()) {
									if (j >= playerX && j < playerX+playerWidth && i == playerY) {
										drawPlayerNum(playerNum); //middle
									}else{
										drawPlayer();
									}
								}else{
									drawDeadPlayer();
								}
						}else{
							if (i == shotInitialY && !isPlayerSpace(i,j)) {
								if ((bulletDirection == 1 && j >= s.x) || (bulletDirection == -1 && j <= s.x)) {
									//if the bullet hits a person
									drawBullet();
								}else
								{
									drawSpace();
								}
							}else{
								drawSpace();
							}
						}
					}
			}
			cout << endl;
		}
	}


	Land::Land(int w, int h, int nP, Player *p, int playerWidth, int playerHeight, double gravity)
	{
		maxWidth = w;
		maxHeight = h;
		numPlayers = nP;
		players = p;
		this -> shot = shot;
		this -> playerWidth = playerWidth;
		this -> playerHeight = playerHeight;
		this -> gravity = gravity;
	}

	Land::Land(void)
	{
	}

	Land::~Land(void)
	{
	}

