#ifndef PLAYERRADIOUS_H
#define PLAYERRADIOUS_H

#include <SDL2/SDL.h>
#include <SDL_render.h>

#include <cmath>
#include <vector>

class Npc;
class Player;
class Clock;
class Layout1;
class Key;
class Camera;
class Wall;

class PlayerRadious {
	float x, y;
	float oldX, oldY;
	int width = 400, height = 500;

   public:
	friend Player;
	bool contact = 0;
    bool access = 0;
    bool isContact(Player* player, Key* key, std::vector<Wall>* walls);
	void update(Player*);
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

