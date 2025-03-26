#ifndef LAYOUT_H
#define LAYOUT_H

#include <SDL2/SDL.h>

#include <vector>

#include "Wall.h"
class Game;

class Layout1 {
   public:
	std::vector<Wall> lines;

	Layout1(float, float);
};

#endif
