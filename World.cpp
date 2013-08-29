#include "stdafx.h"
#include "World.h"
#include "Land.h"
#include "Player.h"
#include "Shot.h"
#include <iostream>
#include <ctime>
#include <string>
#include "Player.h"

using namespace std;

int World::getWinningPlayer() {
	int playersRemaining = 0;
	for (int i = 0; i < numPlayers; i++) {
			if (players[i].isAlive()) {
				return i+1;
			}
	}
	return playersRemaining;
}

int World::getPlayersRemaining() {
	int playersRemaining = 0;
	for (int i = 0; i < numPlayers; i++) {
			if (players[i].isAlive()) {
				playersRemaining++;
			}
	}
	return playersRemaining;
}

void World::doShot(int playerIndex, int velocity, int angle) {
	int playerX = getPlayerLocation(playerIndex);
	int playerY = l.getYForX(playerX) + playerHeight+1;
	Shot s = Shot(playerX, playerY, velocity, angle, gravity);
	system("cls");
	l.drawMap(s);
}

void World::mainLoop() {
		while (getPlayersRemaining() > 1) {
			for (int i = 0; i < numPlayers; i++) {
				if (players[i].isAlive()) {
					currentPlayer = i+1;
					l.setCurrentPlayer(currentPlayer);
					int angle = -1;
					int velocity = -1;
					int playerNumber = i+1;
					cout << endl << endl;
					while (angle < 0 || angle > 180) {
						cout << "Player" << playerNumber << ": Enter an angle between 0 and 180 (0 is East, 180 is West):" << endl;
						cin >> angle;
						if (angle < 0 || angle > 180) {
							cout << "Invalid Choice." << endl;
						}
					}
					cout << endl << endl;
					while ( velocity < 1 || velocity > 100) {
						cout << "Enter a velocity between 1 and 100:" << endl;
						cin >> velocity;
						if ( velocity < 1 || velocity > 100) {
							cout << "Invalid Choice." << endl;
						}
					}
					doShot(playerNumber, velocity, angle);
				}
			}
		}
}

bool World::checkIfEmpty(Player pPosition[], int position, int upTo) {
		for (int i = 0; i < upTo; i++ ) {
			if ((pPosition[i].getPos() > position-playerWidth) && (pPosition[i].getPos() < position+playerWidth)) {
				//taken!
				return false;
			}
		}
		return true;
}


Player* World::populatePlayerPosition () {
		Player *pPosition = new Player[numPlayers];
		srand( time( NULL ) );
		int outsideBound = playerWidth/2;
		outsideBound += 1;
		for (int playerCount = 0; playerCount < numPlayers; playerCount++) {
			int playerX = rand() % (width-(playerWidth*2)) + playerWidth;
			//make sure there is enough room
			while (!checkIfEmpty(pPosition, playerX, playerCount)) {
				playerX = rand() % (width-(playerWidth*2)) + playerWidth;
			}

			int playerMiddleHeight = playerHeight/2;
			playerMiddleHeight++;
			int playerY = l.getYForX(playerX) + playerMiddleHeight;
			cout << playerY << ", ";
			pPosition[playerCount] = Player(playerWidth, playerHeight, playerX, playerY, 1, playerCount+1);
		}
		return pPosition;
		delete [] pPosition;
}

int World::getPlayerLocation(int player) {
	int playerLocation = players[player-1].getPos();
	return playerLocation;
}

void World::init() {
	//Create Players
	l = Land(width, height, numPlayers, players, playerWidth, playerHeight, gravity);
	l.setMap();
	cout << endl << "Map set..." << endl;
	players = populatePlayerPosition();
	cout << "Players populated..." << endl;
	l.setPlayers(players);
	l.drawMap();
}


World::World(int numPlayers, int width, int height, int playerWidth, int playerHeight, double gravity)
{
	this -> numPlayers = numPlayers;
	this -> width = width;
	this -> height = height;
	this -> playerWidth = playerWidth;
	this -> playerHeight = playerHeight;
	this -> gravity = gravity;
	this -> currentPlayer = 1;
}


World::~World(void)
{
}
