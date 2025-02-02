#ifndef SQUARE_H
#define SQUARE_H

#include <SDL2/SDL.h>
#include "Line.h"

class Square {
  float x, y;
  int size;
  float speed;

public:
  Square(float, float, int, float);   // Constructor
  void handleInput(SDL_Event &event); // Handle keyboard input
  void render(SDL_Renderer *renderer);
  void update(Line);
  float getX() const { return x; }
  float getY() const { return y; }
};

#endif // SQUARE_H
