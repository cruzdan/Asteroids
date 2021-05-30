#pragma once
#include <SDL.h>
//bullet
struct Bullet {
	double multiplicatorX; // cos(angle - 90) distance to move the bullet in X
	double multiplicatorY; // sin(angle - 90) distance to move the bullet in Y
	bool active;
	int angle;
	SDL_Rect rect;

};