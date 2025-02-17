#include "include/Player.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_joystick.h>
#include <SDL_keyboard.h>
#include <SDL_scancode.h>
#include <SDL_stdinc.h>

#include <cmath>
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <iostream>

#include "include/GameObject.h"
using namespace std;
// Constructor
Player::Player(float x, float y, int sizeWidth, int sizeHeight, float speed)
	: GameObject(x, y, sizeWidth, sizeHeight), speed(speed) {
	int frameWidth = 128;	// Width of each frame
	int frameHeight = 128;	// Height of each frame
	int frameCount = 6;		// Number of frames in the animation
	for (int i = 0; i < frameCount; ++i) {
		frames.push_back({i * frameWidth, 0, frameWidth, frameHeight});
	}
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

void Player::update(Clock *clock) {
	if (clock->last_tick_time - lastFrameTime > 150) {
		currentFrame = (currentFrame + 1) % frames.size();	// Cycle through frames
		lastFrameTime = clock->last_tick_time;
	}
}
// RENDERER
void Player::render(SDL_Renderer *renderer) {
	if (spriteSheet) {
		SDL_Rect destRect = {static_cast<int>(x) - 43, static_cast<int>(y) - 64 /* - sizeHeight + 10*/, 128, 128};
		SDL_Rect hitBox = {static_cast<int>(x), static_cast<int>(y), sizeWidth, sizeHeight};
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // White color
		SDL_RenderFillRect(renderer, &hitBox);
		SDL_RenderCopy(renderer, spriteSheet, &frames[currentFrame], &destRect);
	} else {
		SDL_Surface *surface = IMG_Load("assets/idle.png");
		if (!surface) {
			std::cerr << "Failed to load sprite sheet: " << IMG_GetError() << "\n";
			return;
		}

		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		if (!texture) {
			std::cerr << "Failed to create texture from sprite sheet: " << SDL_GetError() << "\n";
		}
		spriteSheet = texture;
	}
}
