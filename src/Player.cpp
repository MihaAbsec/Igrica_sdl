#include "include/Player.h"

#include <SDL2/SDL.h>
#include <SDL_joystick.h>
#include <SDL_keyboard.h>
#include <SDL_scancode.h>
#include <SDL_stdinc.h>

#include <cmath>
#include <glm/glm.hpp>
#include <glm/vec2.hpp>

#include "include/GameObject.h"
using namespace std;
// Constructor
Player::Player(float x, float y, int sizeWidth, int sizeHeight, float speed)
	: GameObject(x, y, sizeWidth, sizeHeight), speed(speed) {
	/*this->x = x;
	this->y = y;
	this->sizeWidth = sizeWidth;
	this->sizeHeight = sizeHeight;*/
}

// Handle keyboard input
void Player::handleInput(SDL_Event &event, Clock *clock) {
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	glm::vec2 movement(0.0f, 0.0f);

	if (state[SDL_SCANCODE_W]) {
		movement.y -= 1.0f;
	}
	if (state[SDL_SCANCODE_S]) {
		movement.y += 1.0f;
	}
	if (state[SDL_SCANCODE_D]) {
		movement.x += 1.0f;
	}
	if (state[SDL_SCANCODE_A]) {
		movement.x -= 1.0f;
	}

	if (glm::length(movement) > 0.0f) {
		oldX = x;
		oldY = y;

		// Normalize movement to avoid diagonal speed boost
		movement = glm::normalize(movement);

		// Apply speed and delta time
		movement *= (speed * clock->delta * 0.4f);

		// Update position
		x += movement.x;
		y += movement.y;
	}
}

void Player::update(Line line) {
	// zgornja plast
	if (y + sizeHeight > line.getY() && !(oldY + sizeHeight > line.getY()))
		if (!(x + sizeWidth <= line.getX() || x >= line.getX() + line.getW()))
			y = line.getY() - sizeHeight;
	// spodnja plast
	if (y < line.getY() + line.getH() && !(oldY < line.getY() + line.getH()))
		if (!(x + sizeWidth <= line.getX() || x >= line.getX() + line.getW()))
			y = line.getY() + line.getH();
	// leva plast
	if (x + sizeWidth > line.getX() && !(oldX + sizeWidth > line.getX()))
		if (!(y + sizeHeight <= line.getY() || y >= line.getY() + line.getH()))
			x = line.getX() - sizeWidth;
	// desna plast
	if (x < line.getX() + line.getW() && !(oldX < line.getX() + line.getW()))
		if (!(y + sizeHeight <= line.getY() || y >= line.getY() + line.getH()))
			x = line.getX() + line.getW();
}

// Render the square
