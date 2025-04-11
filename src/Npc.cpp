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
#include <ios>
#include <iostream>
#include <random>
#include <vector>

#include "include/Collision.h"
#include "include/GameObject.h"
#include "include/Layout1.h"
#include "include/NpcFov.h"
// Constructor
Npc::Npc(int worldW, int worldH, int sizeWidth, int sizeHeight, float speed, std::vector<Wall> *walls, Game *game, Camera *camera)
	: GameObject(0, 0, sizeWidth, sizeHeight), speed(speed) {
	float length;
	do {
		x = std::rand() % worldW;
		y = std::rand() % worldH;
	} while (NpcCollision(walls) || spawnCollision(game, camera, this));
	spawnX = x;
	spawnY = y;
	shooter = std::rand() % 2;
	last_npc_time = std::rand() % 1999;
	fov = new NpcFov;
	createSprite();
}

void Npc::createSprite() {
	officer = nullptr;
	for (int i = 0; i < 7; ++i) {
		runFrames.push_back({i * 32, 288, 32, 32});
		shootFrames.push_back({i * 32, 864, 32, 32});
	}
	for (int i = 0; i < 4; ++i)
		walkFrames.push_back({i * 32, 32, 32, 32});

	idleFrame = {0, 0, 32, 32};
}
void Npc::update(Clock *clock, std::vector<Wall> *walls) {
	fov->update(this, walls);
	if (clock->last_tick_time - lastFrameTime > 150) {
		currentFrameRun = (currentFrameRun + 1) % runFrames.size();
		currentFrameWalk = (currentFrameWalk + 1) % walkFrames.size();
		currentFrameShoot = (currentFrameShoot + 1) % shootFrames.size();
		lastFrameTime = clock->last_tick_time;
	}
}

// NPC movement
void Npc::movement(Clock *clock, std::vector<Wall> *walls, Player *player, std::vector<Bullet> *bullets) {
	const Uint32 directionChangeInterval = 2000;
	if (fov->contact) {
		fov->isContact(this, player, clock, walls, bullets);
		for (Wall wall : *walls)
			moveCollision(this, &wall);
	}
	if (!fov->contact /* || fov->access*/) {
		if (clock->last_tick_time - last_npc_time >= directionChangeInterval || NpcCollision(walls) || fov->access) {
			headDirection = std::rand() % 4;
			last_npc_time = clock->last_tick_time;
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

			if (NpcCollision(walls)) {
				x = oldX;
				y = oldY;

				headDirection = std::rand() % 4;
			}
		}

		float dx = abs(x - oldX);
		float dy = abs(y - oldY);
		if (dx < 1.00f && dy < 1.00f)
			count++;
		if (count > 100) {
			move = 0;
			if (!(dx == 0.00f && dy == 0.00f))
				count = 0;
		} else
			move = 1;
	}
}

void Npc::shooting(Player *player, std::vector<Bullet> *bullets, Clock *clock) {
	if (!shooter)
		return;
	if (clock->last_tick_time - last_shot_time >= 850) {
		bullets->push_back(Bullet(0, getGunX(), getGunY(), 5, 5, 1,
								  player->getX() + (player->getW() / 2),
								  player->getY() + (player->getH() / 2)));
		last_shot_time = clock->last_tick_time;
	}
}

bool Npc::NpcCollision(std::vector<Wall> *walls) {
	for (Wall wall : *walls)
		if (collision(this, wall)) {
			return true;
		}
	return false;
}
void Npc::render(SDL_Renderer *renderer, Camera *camera) {
    if (!renderer || !camera) return;
	// fov->render(renderer, camera);
	if (!officer) {
		createSprite(officer, renderer);
		if (!officer) return;
	}
	// SDL_Rect destRect = {static_cast<int>(x) - 28, static_cast<int>(y) - 3, 80, 80};
	// SDL_Rect hitBox = {static_cast<int>(x), static_cast<int>(y), sizeWidth, sizeHeight};
	// SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect destRect = {
		static_cast<int>(x - camera->x) - 28,
		static_cast<int>(y - camera->y) - 3,
		80,
		80};
	if (destRect.w <= 0 || destRect.h <= 0) {
		return;	 // Skip rendering invalid rectangles
	}
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
	if (move == 3)
		if (turn)
			SDL_RenderCopyEx(renderer, officer, &shootFrames[currentFrameRun], &destRect, 0, NULL, SDL_FLIP_HORIZONTAL);
		else if (!turn)
			SDL_RenderCopy(renderer, officer, &shootFrames[currentFrameRun], &destRect);
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
