#pragma once
#include "Player.h"
#include "Land.h"

class World
{
	int numPlayers, width, height, currentPlayer;
	double gravity;
	Player *players;
	Land l;

public:
	int playerWidth, playerHeight;
	void init();
	void reset();
	void mainLoop();
	bool checkIfEmpty(Player pPosition[], int position, int upTo); // checks if playerX is empty
	Player* populatePlayerPosition ();
	int getPlayersRemaining();
	int getWinningPlayer();
	int getPlayerLocation(int player);
	int getAltitude(int x);
	int getLastShotHeight(int x);
	void resetLastShot();
	void doShot(int playerIndex, int velocity, int angle);
	bool isDead(int playerIndex);
	World(int numPlayers, int width, int height, int playerWidth, int playerHeight, double gravity);
	~World(void);
};

