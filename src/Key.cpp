#include "include/Key.h"

#include <ctime>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <iostream>
#include <vector>

#include "include/Collision.h"
#include "include/GameObject.h"
#include "include/Game.h"
#include "include/Camera.h"

Key::Key(int width, int height, std::vector<Wall>* walls, Game* game, Camera* camera)
	: GameObject(0, 0, 32, 16), texture(nullptr) {
	srand(time(NULL));
	float length;
	do {
		x = rand() % width;
		y = rand() % height;
	} while (KeyCollision(walls) || spawnCollision(game, camera, this));
	oldX = x;
	oldY = y;
}

bool Key::KeyCollision(std::vector<Wall>* walls) {
	for (Wall wall : *walls)
		if (collision(this, wall)) {
			return true;
		}
	return false;
}

void Key::render(SDL_Renderer* renderer, Camera* camera) {
	if (!texture) {
		SDL_Surface* surface = IMG_Load("assets/key.png");
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		if (!texture) {
			std::cerr << "Failed to create texture from surface: " << SDL_GetError() << "\n";
			return;
		}
	}

	SDL_Rect destRect = {static_cast<int>(x - camera->x), static_cast<int>(y - camera->y), sizeWidth, sizeHeight};
	SDL_RenderCopy(renderer, texture, nullptr, &destRect);
}

Key::~Key() {
	if (texture) {
		SDL_DestroyTexture(texture);
	}
}
