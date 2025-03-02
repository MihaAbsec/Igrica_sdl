#ifndef NPCFOV_H
#define NPCFOV_H

#include <SDL2/SDL.h>
#include <SDL_render.h>

#include <cmath>

class Npc;
class Player;
class Clock;
class Layout1;
class Camera;

class NpcFov {
	float x, y;
	float oldX, oldY;
	int width = 200, height = 250;

   public:
	friend Npc;
	bool contact = 0;
    bool access = 0;
	void isContact(Npc*, Player*, Clock*, Layout1*);
	void update(Npc*, Layout1*);
	void render(SDL_Renderer*, Camera*);
	float getX() const {
		return x;
	}
	float getY() const {
		return y;
	}
	int getW() const {
		return width;
	}
	int getH() const {
		return height;
	}
	float getoldX() const {
		return oldX;
	}
	float getoldY() const {
		return oldY;
	}
	void giveWH(int W, int H) {
		width = W;
		height = H;
	}
	void giveXY(float X, float Y) {
		x = X;
		y = Y;
	}
};

#endif
