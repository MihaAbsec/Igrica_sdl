#include "include/Line.h"
#include <SDL2/SDL.h>

Line::Line(float x, float y, int width, int height){
    this->x = x;
    this->y = y;
    this->sizeHeight = height;
    this->sizeWidth = width;
}

