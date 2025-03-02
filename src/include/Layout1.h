#ifndef LAYOUT_H
#define LAYOUT_H

#include <SDL2/SDL.h>

#include <vector>

#include "Line.h"
class Game;

class Layout1 {
   public:
	std::vector<Line> lines;

	Layout1(float, float);
};

#endif
