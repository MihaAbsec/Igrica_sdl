#ifndef LINE_H
#define LINE_H

#include <SDL2/SDL.h>

#include "GameObject.h"

class Line : public GameObject {
   public:
	Line(float x, float y, int sizeWidth, int sizeHeight)
		: GameObject(x,y,sizeWidth, sizeHeight){}
};

#endif
