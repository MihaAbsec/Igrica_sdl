#include "include/Key.h"

#include <ctime>
#include <iostream>

#include "include/Collision.h"
#include "include/GameObject.h"

Key::Key(int width, int height, Layout1* layout)
	: GameObject(0, 0, 32,16), texture(nullptr) {
	srand(time(NULL));
	do {
		x = rand() % ((width - 50) - 50) + 50;
		y = rand() % height;
	} while (KeyCollision(layout));
}

bool Key::KeyCollision(Layout1* layout) {
	for (Wall line : layout->lines)
		if (collision(this, line)) {
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
