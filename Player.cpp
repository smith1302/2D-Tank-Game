#include "stdafx.h"
#include "Player.h"

	bool Player::isAlive() {
		if (health <= 0) {
			return false;
		}else{
			return true;
		}
	}

	int Player::getWidth() {
		return width;
	}

	int Player::getHeight() {
		return height;
	}

	int Player::getPos() {
		return xPos;
	}

	int Player::getYPos() {
		return yPos;
	}

	int Player::getHealth() {
		return health;
	}

	void Player::setHealth(int newHealth) {
		health = newHealth;
	}

	int Player::getPlayerNum() {
		return playerNum;
	}

Player::Player(int width, int height, int xPos, int yPos, int health, int playerNum)
{
	this -> width = width;
	this -> height = height;
	this -> xPos = xPos;
	this -> yPos = yPos;
	this -> health = health;
	this -> playerNum = playerNum;
}

Player::Player(void)
{
}


Player::~Player(void)
{
}
