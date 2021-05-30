#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include "Bullet.h"
#include "Enemy.h"

extern int SCREEN_WIDTH ;
extern int SCREEN_HEIGHT;
extern int MS;
extern double PI;
extern int MAX_BULLETS;
extern int MAX_ENEMIES;

extern SDL_Window* window;
extern SDL_Renderer* renderer;

extern int lifes;
extern bool gameOver;

//image
extern SDL_Texture* backgroundTexture;
extern SDL_Texture* shipTexture;
extern SDL_Texture* rocketTexture;
extern SDL_Texture* asteroidTexture;
extern SDL_Rect shipRect;
extern SDL_Rect backgroundRect;

//music and sounds
extern Mix_Music* music;
extern Mix_Chunk* sound;

//ship movement
extern int angle;
extern int shipVelocity;
extern int speedBullet;
extern double mulX;
extern double mulY;
extern int timerShip;

//joystick
extern SDL_Joystick* joystick;
extern int totalJoysticks;

extern struct Bullet bullet[];
extern int bulletTimer;
extern int bulletsAvailable;

extern struct Enemy enemy[];
extern int timerEnemys;
extern int totalEnemys;

extern int indexMenu;
//menu 0
extern SDL_Texture* titleTexture;
extern SDL_Rect titleRect;
extern SDL_Texture* playTexture;
extern SDL_Rect playRect;
extern SDL_Texture* controlsTexture;
extern SDL_Rect controlsRect;
extern SDL_Texture* exitTexture;
extern SDL_Rect exitRect;

//menu 1
extern SDL_Texture* scoreTexture;
extern SDL_Rect scoreRect;
extern SDL_Texture* lifeTexture;
extern SDL_Rect lifeRect;
extern SDL_Rect shipLifeRect;
extern SDL_Texture* numberScore;
extern SDL_Rect numberScoreRect;
extern SDL_Rect bulletAvailableRect;
extern int score;
extern int k; 

//menu 2
extern SDL_Texture* instruction1Texture;
extern SDL_Rect instruction1Rect;
extern SDL_Texture* instruction2Texture;
extern SDL_Rect instruction2Rect;
extern SDL_Texture* instruction3Texture;
extern SDL_Rect instruction3Rect;
extern SDL_Texture* instruction4Texture;
extern SDL_Rect instruction4Rect;