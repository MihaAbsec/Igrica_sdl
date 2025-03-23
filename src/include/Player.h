#ifndef SQUARE_H
#define SQUARE_H

#include <SDL2/SDL.h>
#include <SDL_render.h>

#include <vector>

#include "Clock.h"
#include "GameObject.h"
#include "Mouse.h"

class Player : public GameObject {
    int lives;
	// GUN
	float gunX, gunY;

	float speed;
	const float prevSpeed = speed;
	bool turn = 0;
	bool move = 0;
	// sprites
	SDL_Texture* agent;
	SDL_Rect idleFrame;
	SDL_Rect shootFrame;
	std::vector<SDL_Rect> runFrames;
	std::vector<SDL_Rect> shootFrames;
	int currentFrameRun;	
	int currentFrameShoot;	
	Uint32 lastFrameTime;	

   public:
	void createSprite();
	void createSprite(SDL_Texture*&, SDL_Renderer*);
	void shooting(bool shot);
	Player(float, float, int, int, float);
	void handleInput(SDL_Event& event, Clock* clock);
	void update(Clock*);
	void render(SDL_Renderer* renderer, Mouse, int, int, Camera*);
	float getGunX() const {
		return gunX;
	}
	float getGunY() const {
		return gunY;
	}
	void bulletSpawnFix(Mouse);
    void operator--();
    int getLives();
};

#endif	// SQUARE_H
