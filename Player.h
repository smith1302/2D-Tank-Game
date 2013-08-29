#pragma once
class Player
{
	int width, height, xPos, yPos, health, playerNum;
	public:
	int getWidth();
	int getHeight();
	int getPos();
	int getYPos();
	int getHealth();
	int getPlayerNum();
	void setHealth(int newHealth);
	bool isAlive();
	Player(int width, int height, int xPos, int yPos, int health, int playerNum);
	Player(void);
	~Player(void);
};

