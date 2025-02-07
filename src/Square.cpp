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
Square::Square(float x, float y, int sizeWidth, int sizeHeight, float speed)
	: x(x), y(y), sizeWidth(sizeWidth), sizeHeight(sizeHeight), speed(speed) {}

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
	// zgornja plast
	if (y + sizeHeight > line.getY() && !(oldY + sizeHeight > line.getY()))
		if (!(x + sizeWidth < line.getX() || x > line.getX() + line.getW()))
			y = line.getY() - sizeHeight;
	// spodnja plast
	if (y < line.getY() + line.getH() && !(oldY < line.getY() + line.getH()))
		if (!(x + sizeWidth < line.getX() || x > line.getX() + line.getW()))
			y = line.getY() + line.getH();
	// leva plast
	if (x + sizeWidth > line.getX() && !(oldX + sizeWidth > line.getX()))
		if (!(y + sizeHeight < line.getY() || y > line.getY() + line.getH()))
			x = line.getX() - sizeWidth;
	// desna plast
	if (x < line.getX() + line.getW() && !(oldX < line.getX() + line.getW()))
		if (!(y + sizeHeight < line.getY() || y > line.getY() + line.getH()))
			x = line.getX() + line.getW();
}

// Render the square
void Square::render(SDL_Renderer *renderer) {
	SDL_Rect rect = {static_cast<int>(x), static_cast<int>(y), sizeWidth, sizeHeight};
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // White color
	SDL_RenderFillRect(renderer, &rect);
}
