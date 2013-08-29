#pragma once

class Shot
{
public:
	int x, y, velocity, angle, power, direction;
	int getYForX(int x, double gravity);
	int getDirection();
	Shot(int x, int y, int velocity, int angle, int power);
	Shot(void);
	~Shot(void);
};

