#ifndef WALL_H
#define WALL_H

#include <SDL2/SDL.h>

#include "GameObject.h"

class Wall : public GameObject {
   public:
	Wall(float x, float y, int sizeWidth, int sizeHeight)
		: GameObject(x,y,sizeWidth, sizeHeight){}
};

#endif
