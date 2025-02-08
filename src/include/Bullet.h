#ifndef BULLET_H
#define BULLET_H

#include <SDL2/SDL.h>

#include "GameObject.h"

class Bullet : public GameObject {
    float speed;
   public:
	Bullet(float, float, int, int, float);
};

#endif

