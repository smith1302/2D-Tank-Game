#pragma once
#include "Player.h"
#include "Shot.h"

class Land {
		int maxWidth, maxHeight, numPlayers, currentPlayer, playerWidth, playerHeight;
		double gravity;
		Player *players;
		Shot shot;
		int *map;
	public:
		Land(int maxWidth, int maxHeight, int numPlayers, Player *p, int playerWidth, int playerHeight, double gravity);
		Land();
		~Land();
		int getYForX(int x);
		void setCurrentPlayer(int currentPlayer);
		void drawMap();
		void drawMap(Shot s);
		void showPositions();
		int* populatePlayerPosition();
		void drawSpace();
		void drawLand();
		void drawPlayer();
		void drawDeadPlayer();
		void drawBullet();
		void drawPlayerNum(int playerNum);
		int predictHit(Shot s);
		void setMap();
		void setPlayers(Player *p);
		bool checkIfEmpty(int pPosition[], int position, int upTo);
		bool currentPlayerPointer(int i, int j);
		int isPlayerSpace(int i, int j);

};

