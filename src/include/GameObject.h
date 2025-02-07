#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL2/SDL.h>

class GameObject {
   protected:
	float x, y;
	int sizeHeight, sizeWidth;
	float oldX = 0, oldY = 0;

   public:
	void render(SDL_Renderer *renderer) {
	SDL_Rect rect = {static_cast<int>(x), static_cast<int>(y), sizeWidth, sizeHeight};
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // White color
	SDL_RenderFillRect(renderer, &rect);
}	virtual void giveXY(int dx, int dy) {
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
