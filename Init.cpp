#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Variables.h"

bool init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", SDL_GetError(), NULL);
		std::cout << "SDL did not initialize " << std::endl;
		SDL_Quit();
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Image",
			"The image PNG is not working", NULL);
		return false;
	}

	if (TTF_Init() < 0) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Ttf",
			"The ttf is not working", NULL);
		return false;
	}
	if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE,
		&window, &renderer) < 0) {
		std::cout << "window or renderer are not initialized " << std::endl;
		return false;
	}
	SDL_SetWindowTitle(window, "Asteroids");

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Audio",
			"The audio is not working", NULL);
		return false;
	}

	music = Mix_LoadMUS("Child's Nightmare.ogg");
	if (!music) {
		std::cout << "The music is not loaded" << std::endl;
	}
	sound = Mix_LoadWAV("canon.wav");
	if (!sound) {
		std::cout << "The sound is not loaded" << std::endl;
	}
	Mix_VolumeMusic(SDL_MIX_MAXVOLUME / 2);

	return true;
}

void initVariables() {
	srand((unsigned int)time(NULL));

	backgroundRect.x = 0;
	backgroundRect.y = 0;
	backgroundRect.w = SCREEN_WIDTH;
	backgroundRect.h = SCREEN_HEIGHT;

	shipRect.w = SCREEN_HEIGHT / 20;
	shipRect.h = SCREEN_HEIGHT / 10;
	shipRect.x = SCREEN_WIDTH / 2 - shipRect.w / 2;
	shipRect.y = SCREEN_HEIGHT / 2 - shipRect.h / 2;

	scoreRect.x = 0;
	scoreRect.y = 0;
	scoreRect.w = SCREEN_WIDTH / 4;
	scoreRect.h = SCREEN_HEIGHT / 10;

	lifeRect.x = scoreRect.x;
	lifeRect.y = scoreRect.h;
	lifeRect.w = scoreRect.w / 2;
	lifeRect.h = scoreRect.h;

	numberScoreRect.x = scoreRect.w;
	numberScoreRect.y = scoreRect.y;
	numberScoreRect.w = lifeRect.w / 7;
	numberScoreRect.h = lifeRect.h;

	titleRect.x = SCREEN_WIDTH / 10;
	titleRect.y = 0;
	titleRect.w = (int)(SCREEN_WIDTH * 0.8);
	titleRect.h = SCREEN_HEIGHT / 4;

	playRect.x = (int)(SCREEN_WIDTH * 0.3);
	playRect.y = titleRect.h;
	playRect.w = (int)(SCREEN_WIDTH * 0.4);
	playRect.h = SCREEN_HEIGHT / 4;

	controlsRect.x = SCREEN_WIDTH / 10;
	controlsRect.y = playRect.y + playRect.h;
	controlsRect.w = (int)(SCREEN_WIDTH * 0.8);
	controlsRect.h = SCREEN_HEIGHT / 4;

	exitRect.x = (int)(SCREEN_WIDTH * 0.3);
	exitRect.y = controlsRect.y + controlsRect.h;
	exitRect.w = (int)(SCREEN_WIDTH * 0.4);
	exitRect.h = SCREEN_HEIGHT / 4;

	shipLifeRect.h = lifeRect.h;
	shipLifeRect.w = shipLifeRect.h / 2;
	shipLifeRect.y = lifeRect.y;

	instruction1Rect.x = 0;
	instruction1Rect.y = SCREEN_HEIGHT / 10;
	instruction1Rect.w = SCREEN_WIDTH;
	instruction1Rect.h = SCREEN_HEIGHT / 10;

	instruction2Rect.x = SCREEN_WIDTH / 4;
	instruction2Rect.y = instruction1Rect.y + instruction1Rect.h + SCREEN_HEIGHT / 10;
	instruction2Rect.w = SCREEN_WIDTH / 2;
	instruction2Rect.h = SCREEN_HEIGHT / 10;

	instruction3Rect.x = SCREEN_WIDTH / 4;
	instruction3Rect.y = instruction2Rect.y + instruction2Rect.h + SCREEN_HEIGHT / 10;
	instruction3Rect.w = SCREEN_WIDTH / 2;
	instruction3Rect.h = SCREEN_HEIGHT / 10;

	instruction4Rect.x = SCREEN_WIDTH / 8;
	instruction4Rect.y = instruction3Rect.y + instruction3Rect.h + SCREEN_HEIGHT / 10;
	instruction4Rect.w = 3 * SCREEN_WIDTH / 4;
	instruction4Rect.h = SCREEN_HEIGHT / 10;

	for (int i = 0; i < MAX_BULLETS; i++) {
		bullet[i].active = false;
		bullet[i].rect.w = shipRect.w / 2;
		bullet[i].rect.h = shipRect.h / 2;
	}

	for (int i = 0; i < MAX_ENEMIES; i++) {
		enemy[i].active = false;
	}

	bulletAvailableRect.h = bullet[0].rect.h * 2;
	bulletAvailableRect.w = bullet[0].rect.w * 2;
	bulletAvailableRect.y = SCREEN_HEIGHT - bulletAvailableRect.h;
}

void loadImage() {
	SDL_Surface* image;

	image = IMG_Load("images/background.png");
	if (!image) {
		std::cout << "failed in load background image" << std::endl;
	}
	backgroundTexture = SDL_CreateTextureFromSurface(renderer, image);

	image = IMG_Load("images/ship.png");
	if (!image) {
		std::cout << "failed in load ship image" << std::endl;
	}
	shipTexture = SDL_CreateTextureFromSurface(renderer, image);

	image = IMG_Load("images/rocket.png");
	if (!image) {
		std::cout << "failed in load rocket image" << std::endl;
	}
	SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, 255, 255, 255));
	rocketTexture = SDL_CreateTextureFromSurface(renderer, image);

	image = IMG_Load("images/asteroid.png");
	if (!image) {
		std::cout << "failed in load asteroid image" << std::endl;
	}
	SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, 255, 255, 255));
	asteroidTexture = SDL_CreateTextureFromSurface(renderer, image);

	SDL_FreeSurface(image);
}

void loadJoystick() {
	joystick = SDL_JoystickOpen(0);
	if (!joystick) {
		std::cout << "there is no joystick 1" << std::endl;
	}
	totalJoysticks = SDL_NumJoysticks();
}

void generateMenu() {
	SDL_Color white = { 255,255,255 };
	SDL_Surface* textSurface;
	TTF_Font* font = TTF_OpenFont("Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 4);
	//menu 0
	textSurface = TTF_RenderText_Solid(font, "ASTEROIDS", white);
	titleTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	textSurface = TTF_RenderText_Solid(font, "Play", white);
	playTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	textSurface = TTF_RenderText_Solid(font, "Controls", white);
	controlsTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	textSurface = TTF_RenderText_Solid(font, "Exit", white);
	exitTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	//menu 1
	font = TTF_OpenFont("Oswald-Stencil.ttf", SCREEN_HEIGHT / 10);
	textSurface = TTF_RenderText_Solid(font, "Score: ", white);
	scoreTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	textSurface = TTF_RenderText_Solid(font, "0", white);
	numberScore = SDL_CreateTextureFromSurface(renderer, textSurface);
	textSurface = TTF_RenderText_Solid(font, "Lifes:", white);
	lifeTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	//menu 2
	font = TTF_OpenFont("Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 10);
	textSurface = TTF_RenderText_Solid(font, "Press w,a,s,d or arrows to move the ship", white);
	instruction1Texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	textSurface = TTF_RenderText_Solid(font, "Press space to shoot", white);
	instruction2Texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	textSurface = TTF_RenderText_Solid(font, "Press R to restart", white);
	instruction3Texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	textSurface = TTF_RenderText_Solid(font, "Press esc to go to main menu", white);
	instruction4Texture = SDL_CreateTextureFromSurface(renderer, textSurface);

	TTF_CloseFont(font);
}

/*
Music obtained in https://patrickdearteaga.com
*/