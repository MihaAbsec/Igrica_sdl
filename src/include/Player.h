#ifndef SQUARE_H
#define SQUARE_H

#include <SDL2/SDL.h>
#include <SDL_render.h>

#include <vector>

#include "Clock.h"
#include "GameObject.h"
#include "Mouse.h"

class Player : public GameObject {
	// GUN
	float gunX, gunY;

	float speed;
	const float prevSpeed = speed;
	bool turn = 0;
	bool move = 0;
	// sprites
	SDL_Texture* agent;	 // Sprite sheet texture
	SDL_Rect idleFrame;	 // Animation frames
	SDL_Rect shootFrame;
	std::vector<SDL_Rect> runFrames;  // Animation frames
	std::vector<SDL_Rect> shootFrames;
	int currentFrameRun;	// Current frame of the animation
	int currentFrameShoot;	// Current frame of the animation
	Uint32 lastFrameTime;	// Time of the last frame update

   public:
	void createSprite();
	void createSprite(SDL_Texture*&, SDL_Renderer*);
	void shooting(bool shot);
	Player(float, float, int, int, float);
	void handleInput(SDL_Event& event, Clock* clock);
	void update(Clock*);
	void render(SDL_Renderer* renderer, Mouse);
	float getGunX() const {
		return gunX;
	}
	float getGunY() const {
		return gunY;
	}
    void bulletSpawnFix(Mouse);
};

#endif	// SQUARE_H
