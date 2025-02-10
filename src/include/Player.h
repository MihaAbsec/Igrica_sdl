#ifndef SQUARE_H
#define SQUARE_H

#include <SDL2/SDL.h>

#include "GameObject.h"
#include "Line.h"
#include "Clock.h"

class Player : public GameObject {
	float speed;

   public:
	Player(float, float, int, int, float);
	void handleInput(SDL_Event &event, Clock *clock);	
	void update(Line);
};

#endif	// SQUARE_H
