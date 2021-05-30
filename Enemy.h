#pragma once
#include <SDL.h>
//enemies
struct Enemy {
	bool active;
	double multiplicatorX; // distance to move the bullet in X
	double multiplicatorY; // distance to move the bullet in Y
	int angle;
	int speed;
	int originalAngle;
	SDL_Rect rect;
};