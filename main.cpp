
#include <SDL_mixer.h>
#include <string>
#include "Bullet.h"
#include "Enemy.h"

int SCREEN_WIDTH = 720;
int SCREEN_HEIGHT = 480;
int MS = 50;
double PI = 3.14159265;
int MAX_BULLETS = 8;
int MAX_ENEMIES = 16;

SDL_Window* window;
SDL_Renderer* renderer;
int lifes = 3;
bool gameOver = false;

//image
SDL_Texture* backgroundTexture;
SDL_Texture* shipTexture;
SDL_Texture* rocketTexture;
SDL_Texture* asteroidTexture;
SDL_Rect shipRect;
SDL_Rect backgroundRect;

//music and sounds
Mix_Music* music;
Mix_Chunk* sound;

//ship movement
int angle = 0;//angle of the rotation of the ship
int shipVelocity = 0; //it indicates to where the ship is moving
int speedBullet = SCREEN_HEIGHT / 24;
double mulX = 0; // cos((angle - 90) * PI / 180) static distance to move the ship in X
double mulY = 0; // sin((angle - 90) * PI / 180) static distance to move the ship in Y
int timerShip = 0; // timer to count the seconds to decrement the ship velocity

//joystick
SDL_Joystick* joystick;
int totalJoysticks = 0;

struct Bullet bullet[8];
int bulletTimer = 0;
int bulletsAvailable = 1;

struct Enemy enemy[16];
int timerEnemys = 0;
int totalEnemys = 0;

int indexMenu = 0;
//menu 0
SDL_Texture* titleTexture;
SDL_Rect titleRect;
SDL_Texture* playTexture;
SDL_Rect playRect;
SDL_Texture* controlsTexture;
SDL_Rect controlsRect;
SDL_Texture* exitTexture;
SDL_Rect exitRect;

//menu 1
SDL_Texture* scoreTexture;
SDL_Rect scoreRect;
SDL_Texture* lifeTexture;
SDL_Rect lifeRect;
SDL_Rect shipLifeRect;
SDL_Texture* numberScore;
SDL_Rect numberScoreRect;
SDL_Rect bulletAvailableRect;
int score = 0;
int k = 9; //number to increment the width of the numberScoreRect: it takes the numbers 9,99,999,etc

//menu 2
SDL_Texture* instruction1Texture;
SDL_Rect instruction1Rect;
SDL_Texture* instruction2Texture;
SDL_Rect instruction2Rect;
SDL_Texture* instruction3Texture;
SDL_Rect instruction3Rect;
SDL_Texture* instruction4Texture;
SDL_Rect instruction4Rect;

void detectKeyJoystick();
void detectKey();
void update();
void show();
void generateMenu();
void loadJoystick();
void loadImage();
void initVariables();
bool init();
void close();

int main(int argc, char* args[]) {
	if(!init())
		return -1;
	initVariables();
	loadImage();
	loadJoystick();
	generateMenu();
	while (!gameOver) {
		detectKey();
		if(indexMenu == 1){
			if (totalJoysticks > 0)
				detectKeyJoystick();
			update();
		}
		show();
		SDL_Delay(MS);
	}
	close();
	return 0;
}