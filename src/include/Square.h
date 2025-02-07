#ifndef SQUARE_H
#define SQUARE_H

#include <SDL2/SDL.h>

#include "GameObject.h"
#include "Line.h"

class Square : public GameObject {
	float speed;

   public:
	Square(float, float, int, int, float);
	void handleInput(SDL_Event &event);	
	void update(Line);
};

#endif	// SQUARE_H
