#ifndef SQUARE_H
#define SQUARE_H

#include <SDL2/SDL.h>

#include "Clock.h"
#include "GameObject.h"
#include <vector>

class Player : public GameObject {
	float speed;
	SDL_Texture* spriteSheet;	   // Sprite sheet texture
	std::vector<SDL_Rect> frames;  // Animation frames
	int currentFrame;			   // Current frame of the animation
	Uint32 lastFrameTime;		   // Time of the last frame update

   public:
	Player(float, float, int, int, float);
	void handleInput(SDL_Event& event, Clock* clock);
	void update(Clock*);
	void render(SDL_Renderer* renderer);
};

#endif	// SQUARE_H
