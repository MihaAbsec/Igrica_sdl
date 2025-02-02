#ifndef SQUARE_H
#define SQUARE_H

#include "Line.h"
#include <SDL2/SDL.h>

class Square {
  float x, y;
  int size;
  float speed;
  float oldX = 0, oldY = 0;

public:
  Square(float, float, int, float);   // Constructor
  void handleInput(SDL_Event &event); // Handle keyboard input
  void render(SDL_Renderer *renderer);
  void update(Line);
  float getX() const { return x; }
  float getY() const { return y; }
  float getoldX() const { return oldX; }
  float getoldY() const { return oldY; }
};

#endif // SQUARE_H
