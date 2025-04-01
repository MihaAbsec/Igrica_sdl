#ifndef BULLET_H
#define BULLET_H

#include <SDL2/SDL.h>

#include <cmath>

#include "GameObject.h"
#include "Wall.h"

class Bullet : public GameObject {
   private:
	float dirX, dirY;
	float speed;

   public:
    bool player;
	Bullet(bool, float x, float y, int width, int height, float speed, int targetX, int targetY);
	void update(float deltaTime);
};

#endif
