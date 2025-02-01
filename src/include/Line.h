#ifndef LINE_H
#define LINE_H

#include <SDL2/SDL.h>

class Line {
    float x, y;
    int height, width;
public:
    Line(float, float, int, int);
    void render(SDL_Renderer* renderer);
};

#endif

