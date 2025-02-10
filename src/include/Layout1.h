#ifndef LAYOUT_H
#define LAYOUT_H

#include <SDL2/SDL.h>

#include <vector>

#include "Line.h"

class Layout1 {
   public:
	int SCREEN_WIDTH, SCREEN_HEIGHT;
	std::vector<Line> lines;

	Layout1(int, int);
};

#endif
