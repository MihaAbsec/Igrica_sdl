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

#include "include/Game.h"
#include "include/GameObject.h"
#include "include/Mouse.h"
#include "include/PlayerRadious.h"
using namespace std;
// Constructor
Player::Player(float x, float y, int sizeWidth, int sizeHeight, float speed)
	: GameObject(x, y, sizeWidth, sizeHeight), speed(speed) {
	lives = 3;
    radious = new PlayerRadious;
	createSprite();
}

void Player::createSprite() {
	agent = nullptr;
	for (int i = 0; i < 7; ++i) {
		runFrames.push_back({i * 32, 64, 32, 32});
	}
	for (int i = 0; i < 2; ++i)
		shootFrames.push_back({i * 32, 256, 32, 32});
	idleFrame = {0, 0, 32, 32};
	shootFrame = {0, 256, 32, 32};
}

// Handle keyboard input
void Player::handleInput(SDL_Event &event, Clock *clock) {
    radious->update(this);
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	glm::vec2 movement(0.0f, 0.0f);

	if (state[SDL_SCANCODE_W]) {
		movement.y -= 1.0f;
	}
	if (state[SDL_SCANCODE_S]) {
		movement.y += 1.0f;
	}
	if (state[SDL_SCANCODE_D]) {
		turn = 0;
		movement.x += 1.0f;
	}
	if (state[SDL_SCANCODE_A]) {
		turn = 1;
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
		// x -= sizeWidth/2;
		// y -= sizeHeight/2;
		move = 1;
	} else
		move = 0;
}
void Player::shooting(bool shot) {
	if (shot) {
		speed = prevSpeed * 0.5;
	} else if (!shot) {
		if (speed != prevSpeed)
			speed += 0.001;
		if (speed > prevSpeed)
			speed = prevSpeed;
	}
}

void Player::bulletSpawnFix(Mouse mouse) {
	gunY = y + (float)sizeHeight / 2 - 14;
	if (mouse.getWorldX() < x) {
		gunX = x - 18;
	} else {
		gunX = x + sizeWidth + 14;
	}
}

void Player::update(Clock *clock) {
	if (clock->last_tick_time - lastFrameTime > 150) {
		currentFrameRun = (currentFrameRun + 1) % runFrames.size();
		currentFrameShoot = (currentFrameShoot + 1) % shootFrames.size();
		lastFrameTime = clock->last_tick_time;
	}
}
// RENDERER
void Player::render(SDL_Renderer *renderer, Mouse mouse, int centerX, int centerY, Camera *camera) {
	// std::cout << (int)x << " " << (int)y << '\r';
	// std::cout << std::flush;
    //radious->render(renderer, amera); 
	if (!agent) {
		createSprite(agent, renderer);
	}
	SDL_Rect destRect = {
		static_cast<int>((x - camera->x) - 28),
		static_cast<int>((y - camera->y) - 5),
		80, 80};
	// SDL_Rect destRect = {centerX - 28, centerY - 5, 80, 80};
	//  SDL_Rect hitBox = {centerX/* - sizeWidth / 2*/, centerY/* - sizeHeight / 2*/, sizeWidth, sizeHeight};
	//  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // White color
	//  SDL_RenderFillRect(renderer, &hitBox);
	if (speed != prevSpeed && !move) {
		if (mouse.getWorldX() < x)
			SDL_RenderCopyEx(renderer, agent, &shootFrame, &destRect, 0, NULL, SDL_FLIP_HORIZONTAL);
		else
			SDL_RenderCopy(renderer, agent, &shootFrame, &destRect);

	} else if (speed != prevSpeed && move) {
		if (mouse.getWorldX() < x)
			SDL_RenderCopyEx(renderer, agent, &shootFrames[currentFrameShoot], &destRect, 0, NULL, SDL_FLIP_HORIZONTAL);
		else
			SDL_RenderCopy(renderer, agent, &shootFrames[currentFrameShoot], &destRect);

	} else if (!move) {
		if (turn)
			SDL_RenderCopyEx(renderer, agent, &idleFrame, &destRect, 0, NULL, SDL_FLIP_HORIZONTAL);
		if (!turn)
			SDL_RenderCopy(renderer, agent, &idleFrame, &destRect);
	} else if (move) {
		if (turn)
			SDL_RenderCopyEx(renderer, agent, &runFrames[currentFrameRun], &destRect, 0, NULL, SDL_FLIP_HORIZONTAL);
		if (!turn)
			SDL_RenderCopy(renderer, agent, &runFrames[currentFrameRun], &destRect);
	}
}

void Player::createSprite(SDL_Texture *&t, SDL_Renderer *renderer) {
	SDL_Surface *surface = IMG_Load("assets/agent.png");
	if (!surface) {
		std::cerr << "Failed to load sprite sheet: " << IMG_GetError() << "\n";
		return;
	}

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	if (!texture) {
		std::cerr << "Failed to create texture from sprite sheet: " << SDL_GetError() << "\n";
	}
	t = texture;
}

int Player::getLives(){
    return lives;
}

int Player::getKills(){
    return kills;
}
