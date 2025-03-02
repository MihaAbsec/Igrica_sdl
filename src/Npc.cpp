#include "include/Npc.h"

#include <SDL2/SDL.h>
#include <SDL_joystick.h>
#include <SDL_keyboard.h>
#include <SDL_scancode.h>
#include <SDL_stdinc.h>

#include <algorithm>
#include <cmath>
#include <codecvt>
#include <ctime>
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <iostream>

#include "include/Collision.h"
#include "include/GameObject.h"
#include "include/Layout1.h"
#include "include/NpcFov.h"
// Constructor
Npc::Npc(float x, float y, int sizeWidth, int sizeHeight, float speed)
	: GameObject(x, y, sizeWidth, sizeHeight), speed(speed) {
	fov = new NpcFov;
	createSprite();
}

void Npc::createSprite() {
	officer = nullptr;
	for (int i = 0; i < 7; ++i) {
		runFrames.push_back({i * 32, 64, 32, 32});
		shootFrames.push_back({i * 32, 864, 32, 32});
	}
	for (int i = 0; i < 4; ++i)
		walkFrames.push_back({i * 32, 32, 32, 32});

	idleFrame = {0, 0, 32, 32};
}
void Npc::update(Clock *clock, Layout1 *layout) {
	fov->update(this, layout);
	if (clock->last_tick_time - lastFrameTime > 150) {
		currentFrameRun = (currentFrameRun + 1) % runFrames.size();
		currentFrameWalk = (currentFrameWalk + 1) % walkFrames.size();
		currentFrameShoot = (currentFrameShoot + 1) % shootFrames.size();
		lastFrameTime = clock->last_tick_time;
	}
}

// NPC movement logic
void Npc::movement(Clock *clock, Layout1 *layout, Player *player) {
	srand(time(NULL));
	if (fov->contact) {
		fov->isContact(this, player, clock, layout);
		for (Line line : layout->lines)
			moveCollision(this, &line);
	}
	if (!fov->contact || fov->access) {
		const Uint32 directionChangeInterval = 2000;
		static int count = 0;
		const float movementThreshold = 0.001;	// Adjust this value as needed

		if (clock->last_tick_time - clock->last_npc_time >= directionChangeInterval || NpcCollision(layout)) {
			headDirection = std::rand() % 4;
			clock->last_npc_time = clock->last_tick_time;
		}

		glm::vec2 movement(0.0f, 0.0f);
		switch (headDirection) {
			case 0:	 // Up
				movement.y -= 1.0f;
				break;
			case 1:	 // Right
				movement.x += 1.0f;
				turn = 0;
				break;
			case 2:	 // Down
				movement.y += 1.0f;
				break;
			case 3:	 // Left
				movement.x -= 1.0f;
				turn = 1;
				break;
		}

		if (glm::length(movement) > 0.0f) {
			movement = glm::normalize(movement);

			movement *= (speed * clock->delta * 0.4);

			oldX = x;
			oldY = y;
			x += movement.x;
			y += movement.y;

			if (NpcCollision(layout)) {
				x = oldX;
				y = oldY;

				headDirection = std::rand() % 4;
			}
		}

		// Check if the NPC has moved significantly
		float dx = abs(x - oldX);
		float dy = abs(y - oldY);
		if (dx == 0.00f && dy == 0.00f)
			count++;
		if (count > 600) {
			move = 0;
			if (!(dx == 0.00f && dy == 0.00f))
				count = 0;
		} else
			move = 1;
	}
}

bool Npc::NpcCollision(Layout1 *layout) {
	for (Line line : layout->lines)
		if (collision(this, line)) {
			return true;
		}
	return false;
}
void Npc::render(SDL_Renderer *renderer, Camera *camera) {
	//fov->render(renderer, camera);
	if (!officer) {
		createSprite(officer, renderer);
	}
	// SDL_Rect destRect = {static_cast<int>(x) - 28, static_cast<int>(y) - 3, 80, 80};
	// SDL_Rect hitBox = {static_cast<int>(x), static_cast<int>(y), sizeWidth, sizeHeight};
	// SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect destRect = {
		static_cast<int>(x - camera->x) - 28,
		static_cast<int>(y - camera->y) - 3,
		80,
		80};
	if (!move)
		if (turn)
			SDL_RenderCopyEx(renderer, officer, &idleFrame, &destRect, 0, NULL, SDL_FLIP_HORIZONTAL);
		else
			SDL_RenderCopy(renderer, officer, &idleFrame, &destRect);
	if (move == 1)
		if (turn)
			SDL_RenderCopyEx(renderer, officer, &walkFrames[currentFrameWalk], &destRect, 0, NULL, SDL_FLIP_HORIZONTAL);
		else if (!turn)
			SDL_RenderCopy(renderer, officer, &walkFrames[currentFrameWalk], &destRect);
	if (move == 2)
		if (turn)
			SDL_RenderCopyEx(renderer, officer, &runFrames[currentFrameRun], &destRect, 0, NULL, SDL_FLIP_HORIZONTAL);
		else if (!turn)
			SDL_RenderCopy(renderer, officer, &runFrames[currentFrameRun], &destRect);
}
void Npc::createSprite(SDL_Texture *&t, SDL_Renderer *renderer) {
	SDL_Surface *surface = IMG_Load("assets/officer.png");
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
