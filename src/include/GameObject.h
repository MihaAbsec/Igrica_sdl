#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL2/SDL.h>

#include "NpcFov.h"

class GameObject {
   protected:
	float x, y;
	int sizeHeight, sizeWidth;
	float oldX = 0, oldY = 0;

   public:
	friend NpcFov;
	GameObject();
	GameObject(float x, float y, int sizeWidth, int sizeHeight)
		: x(x), y(y), sizeWidth(sizeWidth), sizeHeight(sizeHeight) {}

	virtual void render(SDL_Renderer* renderer, float cameraX, float cameraY) {
		SDL_Rect rect = {static_cast<int>(x - cameraX), static_cast<int>(y - cameraY), sizeWidth, sizeHeight};
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // White color
		SDL_RenderFillRect(renderer, &rect);
	}
	virtual void giveXY(float dx, float dy) {
		x = dx;
		y = dy;
	}
	virtual float getX() const {
		return x;
	}
	virtual float getY() const {
		return y;
	}
	virtual float getoldX() const {
		return oldX;
	}
	virtual float getoldY() const {
		return oldY;
	}
	virtual int getH() const {
		return sizeHeight;
	}
	virtual int getW() const {
		return sizeWidth;
	}
};

#endif
