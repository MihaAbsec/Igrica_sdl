#include "include/Line.h"
#include <SDL2/SDL.h>

Line::Line(float x, float y, int height, int width){
    Line::x = x;
    Line::y = y;
    Line::height = height;
    Line::width = width;
}

void Line::render(SDL_Renderer* renderer) {
    SDL_Rect rect = { static_cast<int>(x), static_cast<int>(y), height, width };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color
    SDL_RenderFillRect(renderer, &rect);
}
