#ifndef SQUARE_H
#define SQUARE_H

#include <SDL2/SDL.h>

#include "Line.h"

class Square {
	//float x, y;
	int sizeHeight, sizeWidth;
	float speed;
	float oldX = 0, oldY = 0;

   public:
    float x,y;
	Square(float, float, int, int, float);	// Constructor
	void handleInput(SDL_Event &event);		// Handle keyboard input
	void render(SDL_Renderer *renderer);
	void update(Line);
	void giveXY(int dx, int dy) {
		x = dx;
		y = dy;
	}
	float getX() const {
		return x;
	}
	float getY() const {
		return y;
	}
	float getoldX() const {
		return oldX;
	}
	float getoldY() const {
		return oldY;
	}
	int getH() const {
		return sizeHeight;
	}
	int getW() const {
		return sizeWidth;
	}
};

#endif	// SQUARE_H
