#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Variables.h"

void closeTextures() {
	SDL_DestroyTexture(shipTexture);
	SDL_DestroyTexture(backgroundTexture);
	SDL_DestroyTexture(rocketTexture);
	SDL_DestroyTexture(asteroidTexture);
	SDL_DestroyTexture(scoreTexture);
	SDL_DestroyTexture(numberScore);
	SDL_DestroyTexture(lifeTexture);
	SDL_DestroyTexture(titleTexture);
	SDL_DestroyTexture(playTexture);
	SDL_DestroyTexture(controlsTexture);
	SDL_DestroyTexture(exitTexture);
	SDL_DestroyTexture(instruction1Texture);
	SDL_DestroyTexture(instruction2Texture);
	SDL_DestroyTexture(instruction3Texture);
	SDL_DestroyTexture(instruction4Texture);
}

void close() {
	closeTextures();
	SDL_JoystickClose(joystick);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	Mix_FreeChunk(sound);
	Mix_FreeMusic(music);
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}