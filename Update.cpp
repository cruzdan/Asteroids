#include "Variables.h"
#include <iostream>
#include <SDL_ttf.h>
#include <string>

void changeTextScore(std::string newText) {
	TTF_Font* font = TTF_OpenFont("Oswald-Stencil.ttf", SCREEN_HEIGHT / 10);
	SDL_Surface* textSurface;
	SDL_Color white = { 255,255,255 };
	const char* t = newText.c_str();
	textSurface = TTF_RenderText_Solid(font, t, white);
	numberScore = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
}

void restart() {
	for (int i = 0; i < MAX_ENEMIES; i++) {
		enemy[i].active = false;
	}
	for (int i = 0; i < MAX_BULLETS; i++) {
		bullet[i].active = false;
	}
	totalEnemys = 0;
	if (bulletsAvailable < 2)
		bulletsAvailable = 2;

	shipRect.x = SCREEN_WIDTH / 2 - shipRect.w / 2;
	shipRect.y = SCREEN_HEIGHT / 2 - shipRect.h / 2;
	angle = 0;
	shipVelocity = 0;
	bulletTimer = 0;
	timerEnemys = 0;
	if (lifes <= 0) {
		bulletsAvailable = 1;
		lifes = 3;
		score = 0;
		changeTextScore(std::to_string(score));
		k = 9;
		numberScoreRect.w = lifeRect.w / 7;
	}
}

void colisionShipEnemy() {
	for (int i = 0; i < MAX_ENEMIES; i++) {
		if (enemy[i].active && SDL_HasIntersection(&shipRect, &enemy[i].rect)) {
			lifes--;
			restart();
		}
	}
}

void colisionBulletEnemy() {
	for (int i = 0; i < MAX_BULLETS; i++) {
		if (bullet[i].active) {
			for (int j = 0; j < MAX_ENEMIES; j++) {
				if (enemy[j].active && SDL_HasIntersection(&bullet[i].rect, &enemy[j].rect)) {
					bullet[i].active = false;
					enemy[j].active = false;
					totalEnemys--;
					if (score == k) {
						k += 9 * (k + 1);
						numberScoreRect.w += lifeRect.w / 7;
					}
					score++;
					changeTextScore(std::to_string(score));
					if (score % 50 == 0 && lifes < 6)
						lifes++;

					//the big asteroids spawn 2 tiny asteroids
					if (enemy[j].rect.w > SCREEN_HEIGHT / 4) {
						//first asteroid
						int newX, newY, newWidth, newHeight, newAngle;
						newWidth = enemy[j].rect.w / 2;
						newHeight = newWidth;
						newX = enemy[j].rect.x + enemy[j].rect.w / 2 - newWidth / 2;
						newY = enemy[j].rect.y + enemy[j].rect.h / 2 - newHeight / 2;
						newAngle = enemy[j].originalAngle - 22;
						enemy[j].angle = 0;
						enemy[j].rect.x = newX;
						enemy[j].rect.y = newY;
						enemy[j].rect.w = newWidth;
						enemy[j].rect.h = newHeight;
						enemy[j].multiplicatorX = cos(newAngle * PI / 180);
						enemy[j].multiplicatorY = sin(newAngle * PI / 180);
						enemy[j].active = true;
						//second asteroid
						newAngle += 45;
						enemy[j + MAX_ENEMIES / 2].angle = 0;
						enemy[j + MAX_ENEMIES / 2].rect = enemy[j].rect;
						enemy[j + MAX_ENEMIES / 2].multiplicatorX = cos(newAngle * PI / 180);
						enemy[j + MAX_ENEMIES / 2].multiplicatorY = sin(newAngle * PI / 180);
						enemy[j + MAX_ENEMIES / 2].active = true;
						enemy[j + MAX_ENEMIES / 2].speed = enemy[j].speed;
						totalEnemys += 2;
					}
					break;
				}
			}
		}
	}
}

void generateEnemie() {
	if (totalEnemys < MAX_ENEMIES / 2) {
		for (int i = 0; i < MAX_ENEMIES; i++) {
			if (!enemy[i].active) {
				enemy[i].rect.w = rand() % (SCREEN_HEIGHT / 4) + SCREEN_HEIGHT / 24;
				enemy[i].rect.h = enemy[i].rect.w;
				int angleEnemie = rand() % 90;
				/*
				angleEnemy + x represents the asteroid's directionAngle to move it
				*/
				switch (rand() % 4) {
				case 0:
					//the asteroid appears on the superior side
					enemy[i].rect.x = rand() % SCREEN_WIDTH;
					enemy[i].rect.y = 0;
					enemy[i].multiplicatorX = cos((angleEnemie + 45) * PI / 180);
					enemy[i].multiplicatorY = sin((angleEnemie + 45) * PI / 180);
					enemy[i].angle = angleEnemie + 45 - 90;
					enemy[i].originalAngle = angleEnemie + 45;
					break;
				case 1:
					//the asteroid appears on the left side
					enemy[i].rect.x = 0;
					enemy[i].rect.y = rand() % SCREEN_HEIGHT;
					enemy[i].multiplicatorX = cos((angleEnemie - 45) * PI / 180);
					enemy[i].multiplicatorY = sin((angleEnemie - 45) * PI / 180);
					enemy[i].angle = angleEnemie - 45 - 90;
					enemy[i].originalAngle = angleEnemie - 45;
					break;
				case 2:
					//the asteroid appears on the inferior side
					enemy[i].rect.x = rand() % SCREEN_WIDTH;
					enemy[i].rect.y = SCREEN_HEIGHT - enemy[i].rect.h;
					enemy[i].multiplicatorX = cos((angleEnemie + 225) * PI / 180);
					enemy[i].multiplicatorY = sin((angleEnemie + 225) * PI / 180);
					enemy[i].angle = angleEnemie + 225 - 90;
					enemy[i].originalAngle = angleEnemie + 225;
					break;
				case 3:
					//the asteroid appears on the right side
					enemy[i].rect.x = SCREEN_WIDTH - enemy[i].rect.w;
					enemy[i].rect.y = rand() % SCREEN_HEIGHT;
					enemy[i].multiplicatorX = cos((angleEnemie + 135) * PI / 180);
					enemy[i].multiplicatorY = sin((angleEnemie + 135) * PI / 180);
					enemy[i].originalAngle = angleEnemie + 135;
					break;
				}
				enemy[i].speed = rand() % (SCREEN_HEIGHT / 32) + 1;
				enemy[i].active = true;
				totalEnemys++;
				break;
			}
		}
	}
}

void incrementBullet() {
	bulletTimer += MS;
	if (bulletTimer % 250 == 0) {
		if (bulletsAvailable < MAX_BULLETS) {
			bulletsAvailable++;
			bulletTimer = 0;
		}
	}
}

void checkColisions() {
	colisionBulletEnemy();
	colisionShipEnemy();
}

//every 5 seconds an enemy is generated
void updateEnemies() {
	timerEnemys += MS;
	if (timerEnemys > 500) {
		timerEnemys = 0;
		generateEnemie();
	}
}

void decrementShipVelocity() {
	if (shipVelocity != 0) {
		timerShip += MS;
		if (shipVelocity < 0) {
			if (timerShip > 500) {
				if (shipVelocity > -SCREEN_HEIGHT / 240)
					shipVelocity = 0;
				else
					shipVelocity += SCREEN_HEIGHT / 240;
				timerShip = 0;
			}
		}
		else {
			if (timerShip > 500) {
				if (shipVelocity < SCREEN_HEIGHT / 240)
					shipVelocity = 0;
				else
					shipVelocity -= SCREEN_HEIGHT / 240;
				timerShip = 0;
			}
		}
	}
	else {
		timerShip = 0;
	}
}

//this method moves the ship to the contrary side when the ship are on the edges of the game
void checkShip() {
	if (shipRect.x + shipRect.w < 0)
		shipRect.x = SCREEN_WIDTH - 1;
	else if (shipRect.x >= SCREEN_WIDTH)
		shipRect.x = -shipRect.w;
	if (shipRect.y + shipRect.h < 0)
		shipRect.y = SCREEN_HEIGHT - 1;
	else if (shipRect.y >= SCREEN_HEIGHT)
		shipRect.y = -shipRect.h;
}

void moveEnemys() {
	for (int i = 0; i < MAX_ENEMIES; i++) {
		if (enemy[i].active) {
			enemy[i].rect.x += (int)(enemy[i].speed * enemy[i].multiplicatorX);
			enemy[i].rect.y += (int)(enemy[i].speed * enemy[i].multiplicatorY);
			enemy[i].angle += 5;

			if (enemy[i].rect.x > SCREEN_WIDTH || enemy[i].rect.x + enemy[i].rect.w < 0
				|| enemy[i].rect.y > SCREEN_HEIGHT || enemy[i].rect.y + enemy[i].rect.h < 0) {
				totalEnemys--;
				enemy[i].active = false;
			}
		}
	}
}

void moveBullets() {
	for (int i = 0; i < MAX_BULLETS; i++) {
		if (bullet[i].active) {
			bullet[i].rect.x += (int)(speedBullet * bullet[i].multiplicatorX);
			bullet[i].rect.y += (int)(speedBullet * bullet[i].multiplicatorY);
			if (bullet[i].rect.x > SCREEN_WIDTH || bullet[i].rect.x + bullet[i].rect.w < 0
				|| bullet[i].rect.y > SCREEN_HEIGHT || bullet[i].rect.y + bullet[i].rect.h < 0) {
				bullet[i].active = false;
			}
		}
	}
}

void moveShip() {
	if (shipVelocity != 0) {
		shipRect.x += (int)(shipVelocity * mulX);
		shipRect.y += (int)(shipVelocity * mulY);
	}
}

void update() {
	moveShip();
	moveBullets();
	moveEnemys();
	checkShip();
	decrementShipVelocity();
	updateEnemies();
	checkColisions();
	incrementBullet();
}