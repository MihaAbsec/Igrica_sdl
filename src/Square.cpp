#include "include/Square.h"
#include <SDL2/SDL.h>
#include <SDL_joystick.h>
#include <SDL_keyboard.h>
#include <SDL_scancode.h>
#include <SDL_stdinc.h>
#include <cmath>
#include <iostream>
#include <iterator>
using namespace std;
// Constructor
Square::Square(float x, float y, int size, float speed) {
  Square::x = x;
  Square::y = y;
  Square::size = size;
  Square::speed = speed;
}

// Handle keyboard input
void Square::handleInput(SDL_Event &event) {
  const Uint8 *state = SDL_GetKeyboardState(NULL);
  float dx = 0, dy = 0;
  if (state[SDL_SCANCODE_W]) {
    dy -= speed;
  }
  if (state[SDL_SCANCODE_S]) {
    dy += speed;
  }
  if (state[SDL_SCANCODE_D]) {
    dx += speed;
  }
  if (state[SDL_SCANCODE_A]) {
    dx -= speed;
  }
  if (dx != 0 || dy != 0) {
    oldX = x;
    oldY = y;
  }
  if (dx != 0 && dy != 0) {
    dx /= sqrt(2);
    dy /= sqrt(2);
  }
  y += dy;
  x += dx;
}

void Square::update(Line line) {
  /*if (y + size > line.getY() && y < line.getY()) {
    if (abs(y - line.getY()) > abs(size - abs(y - line.getY())))
      if (!(x + size < line.getX() || x > line.getX() + line.getW()))
        y = line.getY() - size;
  }
  if (y < line.getY() + line.getH() && y + size > line.getY() + line.getH()) {
    if (abs(y - line.getY()) < abs(size - abs(y - line.getY()) - line.getH()))
      if (!(x + size < line.getX() || x > line.getX() + line.getW()))
        y = line.getY() + line.getH();
  }
  if (x + size > line.getX() && x < line.getX()) {
    if (abs(x - line.getX()) > abs(size - abs(x - line.getX())))
      if (!(y + size < line.getY() || y > line.getY() + line.getH()))
        x = line.getX() - size;
  }
  if (x < line.getX() + line.getW() && x + size > line.getX() + line.getW()) {
    if (abs(x - line.getX()) < abs(size - abs(x - line.getX()) - line.getW()))
      if (!(y + size < line.getY() || y > line.getY() + line.getH()))
        x = line.getX() + line.getW();
  }*/
  if (y + size > line.getY() && !(oldY + size > line.getY()))
    if (!(x + size < line.getX() || x > line.getX() + line.getW()))
      y = line.getY() - size;
  if (y < line.getY() + line.getH() && !(oldY < line.getY() + line.getH()))
    if (!(x + size < line.getX() || x > line.getX() + line.getW()))
      y = line.getY() + line.getH();
  if (x + size > line.getX() && !(oldX + size > line.getX()))
    if (!(y + size < line.getY() || y > line.getY() + line.getH()))
      x = line.getX() - size;
  if (x < line.getX() + line.getW() && !(oldX < line.getX() + line.getW()))
    if (!(y + size < line.getY() || y > line.getY() + line.getH()))
      x = line.getX() + line.getW();
}

// Render the square
void Square::render(SDL_Renderer *renderer) {
  SDL_Rect rect = {static_cast<int>(x), static_cast<int>(y), size, size};
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color
  SDL_RenderFillRect(renderer, &rect);
}
