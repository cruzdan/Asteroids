#include <SDL.h>
#include "Variables.h"

void showMenu2() {
	SDL_RenderCopy(renderer, instruction1Texture, NULL, &instruction1Rect);
	SDL_RenderCopy(renderer, instruction2Texture, NULL, &instruction2Rect);
	SDL_RenderCopy(renderer, instruction3Texture, NULL, &instruction3Rect);
	SDL_RenderCopy(renderer, instruction4Texture, NULL, &instruction4Rect);
}

void showEnemys() {
	for (int i = 0; i < MAX_ENEMIES; i++) {
		if (enemy[i].active) {
			SDL_RenderCopyEx(renderer, asteroidTexture, NULL, &enemy[i].rect, enemy[i].angle, NULL, SDL_FLIP_NONE);
		}
	}
}

void showBullets() {
	for (int i = 0; i < MAX_BULLETS; i++) {
		if (bullet[i].active) {
			SDL_RenderCopyEx(renderer, rocketTexture, NULL, &bullet[i].rect, bullet[i].angle, NULL, SDL_FLIP_NONE);
		}
	}
}

void showMenu1() {
	SDL_RenderCopyEx(renderer, shipTexture, NULL, &shipRect, angle, NULL, SDL_FLIP_NONE);
	SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
	SDL_RenderCopy(renderer, numberScore, NULL, &numberScoreRect);
	SDL_RenderCopy(renderer, lifeTexture, NULL, &lifeRect);
	for (int i = 0; i < lifes; i++) {
		shipLifeRect.x = lifeRect.w + shipLifeRect.w * i;
		SDL_RenderCopy(renderer, shipTexture, NULL, &shipLifeRect);
	}
	for (int i = 0; i < bulletsAvailable; i++) {
		bulletAvailableRect.x = SCREEN_WIDTH - (MAX_BULLETS - i) * bulletAvailableRect.w;
		SDL_RenderCopy(renderer, rocketTexture, NULL, &bulletAvailableRect);
	}
}

void showMenu0() {
	SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);
	SDL_RenderCopy(renderer, playTexture, NULL, &playRect);
	SDL_RenderCopy(renderer, controlsTexture, NULL, &controlsRect);
	SDL_RenderCopy(renderer, exitTexture, NULL, &exitRect);
}

void show() {
	SDL_RenderCopy(renderer, backgroundTexture, NULL, &backgroundRect);
	switch (indexMenu) {
	case 0:
		showMenu0();
		break;
	case 1:
		showMenu1();
		showBullets();
		showEnemys();
		break;
	case 2:
		showMenu2();
		break;
	}
	SDL_RenderPresent(renderer);
}