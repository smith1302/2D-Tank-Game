#include "stdafx.h"
#include "Shot.h"
#include <math.h>

#define PI 3.14159265

int Shot::getYForX(int x, double gravity) {
	int initialY = this -> y;
	int xDiff = (x-(this->x));
	//if ((angle > 90 && xDiff < 0) || (angle < 90 && xDiff > 0)) {
		//aimed to the right but path is to the left return NULL
		//aimed to the left but path is to the left return NULL
		//return NULL;
	//}
	double angle = ((this -> angle)*PI/180);
	double partA = tan(angle)*xDiff;
	double topPartB = gravity*xDiff*xDiff;
	double bottomPartB = 2*velocity*velocity*cos(angle)*cos(angle);
	int y = initialY + partA - topPartB/bottomPartB;
	return y;
}

int Shot::getDirection() {
	return direction;
}

Shot::Shot(int x, int y, int velocity, int angle, int power)
{

	this -> x = x;
	this -> y = y;
	this -> velocity = velocity;
	this -> angle = angle;
	this -> power = power;
	if (angle > 90) {
		this -> direction = -1;
	}else{
		this -> direction = 1;
	}
}

Shot::Shot(void)
{
}

Shot::~Shot(void)
{
}
