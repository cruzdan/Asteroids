#include <SDL.h>
#include "Variables.h"

void updateMusic() {
	if (!Mix_PlayingMusic()) {
		Mix_PlayMusic(music, -1);
	}
	else if (Mix_PausedMusic()) {
		Mix_ResumeMusic();
	}
	else {
		Mix_PauseMusic();
	}
}

void shoot() {
	if (bulletsAvailable > 0) {
		for (int i = 0; i < MAX_BULLETS; i++) {
			if (!bullet[i].active) {
				bullet[i].active = true;
				bullet[i].multiplicatorX = cos((angle - 90) * PI / 180);
				bullet[i].multiplicatorY = sin((angle - 90) * PI / 180);
				bullet[i].angle = angle;
				bullet[i].rect.x = shipRect.x + shipRect.w / 2 - bullet[i].rect.w / 2 +
					(int)((3 * shipRect.h / 4) * bullet[i].multiplicatorX);
				bullet[i].rect.y = shipRect.y + shipRect.h / 2 - bullet[i].rect.h / 2 +
					(int)((3 * shipRect.h / 4) * bullet[i].multiplicatorY);
				Mix_PlayChannel(-1, sound, 0);
				break;
			}
		}
		bulletsAvailable--;
	}
}



void detectKeyJoystick() {
	if (SDL_JoystickGetAxis(joystick, 0) == SDL_JOYSTICK_AXIS_MAX) {
		angle += SCREEN_HEIGHT / 40;
		if (angle > 360)
			angle = angle % 360;
	}
	else if (SDL_JoystickGetAxis(joystick, 0) == SDL_JOYSTICK_AXIS_MIN) {
		angle -= SCREEN_HEIGHT / 40;
		if (angle < -360)
			angle = -(abs(angle) % 360);
	}
	if (SDL_JoystickGetAxis(joystick, 1) == SDL_JOYSTICK_AXIS_MIN) {
		if (shipVelocity < 10)
			shipVelocity++;
		mulX = cos((angle - 90) * PI / 180);
		mulY = sin((angle - 90) * PI / 180);

	}
	else if (SDL_JoystickGetAxis(joystick, 1) == SDL_JOYSTICK_AXIS_MAX) {
		if (shipVelocity > -10)
			shipVelocity--;
		mulX = cos((angle - 90) * PI / 180);
		mulY = sin((angle - 90) * PI / 180);
	}
	if (SDL_JoystickGetButton(joystick, 0))
		shoot();
}

void detectKey() {
	SDL_Event event;
	const Uint8* keys = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&event)) {
		int typeEvent = event.type;
		if (typeEvent == SDL_QUIT) {
			gameOver = true;
		}
		else if (typeEvent == SDL_KEYDOWN) {
			switch (indexMenu) {
			case 0:
				if (keys[SDL_SCANCODE_ESCAPE]) {
					gameOver = true;
				}
				break;
			case 1:
				if (keys[SDL_SCANCODE_ESCAPE]) {
					indexMenu = 0;
					updateMusic();
				}
				if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT]) {
					angle += SCREEN_HEIGHT / 40;
					if (angle > 360)
						angle = angle % 360;
				}
				else if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT]) {
					angle -= SCREEN_HEIGHT / 40;
					if (angle < -360)
						angle = -(abs(angle) % 360);
				}
				if (keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP]) {
					if (shipVelocity < 10)
						shipVelocity++;
					mulX = cos((angle - 90) * PI / 180);
					mulY = sin((angle - 90) * PI / 180);
				}
				else if (keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN]) {
					if (shipVelocity > -10)
						shipVelocity--;
					mulX = cos((angle - 90) * PI / 180);
					mulY = sin((angle - 90) * PI / 180);
				}
				if (keys[SDL_SCANCODE_SPACE]) {
					shoot();
				}
				break;
			case 2:
				if (keys[SDL_SCANCODE_ESCAPE]) {
					indexMenu = 0;
				}
				break;
			}
		}
		else if (typeEvent == SDL_MOUSEBUTTONDOWN && indexMenu == 0) {
			if (event.button.button == SDL_BUTTON_LEFT) {
				int mouseX;
				int mouseY;
				SDL_GetMouseState(&mouseX, &mouseY);
				SDL_Rect mouseRect;
				mouseRect.x = mouseX;
				mouseRect.y = mouseY;
				mouseRect.w = 1;
				mouseRect.h = 1;
				if (SDL_HasIntersection(&mouseRect, &playRect)) {
					indexMenu = 1;
					updateMusic();
				}
				else if (SDL_HasIntersection(&mouseRect, &controlsRect)) {
					indexMenu = 2;
				}
				else if (SDL_HasIntersection(&mouseRect, &exitRect)) {
					gameOver = true;
				}
			}
		}
	}
}