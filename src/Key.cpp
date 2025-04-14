#include "include/Key.h"

#include <ctime>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <iostream>
#include <vector>

#include "include/Camera.h"
#include "include/Collision.h"
#include "include/Game.h"
#include "include/GameObject.h"

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
void Key::klicajRender(SDL_Renderer* renderer, Player* player, Camera* camera, TTF_Font* font) {
	if (rend) {
		// Izračunaj vektor od igralca do ključa
		glm::vec2 playerPos(player->getX(), player->getY());
		glm::vec2 keyPos(x, y);
		glm::vec2 direction = keyPos - playerPos;

		// Normaliziraj vektor (da dobimo smer)
		if (glm::length(direction) > 0) {
			direction = glm::normalize(direction);

			// Pozicija indikatorja (100 px od igralca v smeri ključa)
			glm::vec2 indicatorPos = playerPos + direction * 100.0f;

			// Pretvori v int za SDL (ker SDL uporablja int za koordinate)
			int indicatorX = static_cast<int>(indicatorPos.x);
			int indicatorY = static_cast<int>(indicatorPos.y);

			// Nastavi barvo za risanje (npr. rumena)
			SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);

			// Če želiš narisati samo "!", lahko uporabiš SDL_ttf za tekst
			// Tukaj prikazujemo preprost krog kot placeholder
			/*SDL_Rect indicatorRect = {
				static_cast<int>(indicatorX - camera->x),
				static_cast<int>(indicatorY - camera->y), 20, 20};
			SDL_RenderFillRect(renderer, &indicatorRect);*/

			// Če imaš SDL_ttf inicializiran, lahko narišeš tekst:
			SDL_Color textColor = {255, 50, 50};
			SDL_Surface* textSurface = TTF_RenderText_Solid(font, " ! ", textColor);
			SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
			SDL_Rect textRect = {
				static_cast<int>(indicatorX - textSurface->w / 2 - camera->x),
				static_cast<int>(indicatorY - textSurface->h / 2 - camera->y),
				textSurface->w * 4, textSurface->h * 2};
			SDL_Rect boxRect = {
				static_cast<int>(indicatorX - camera->x + 20),
				static_cast<int>(indicatorY - camera->y - 10),
				textSurface->w, textSurface->h * 2};

			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
			SDL_RenderFillRect(renderer, &boxRect);
			SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
			SDL_FreeSurface(textSurface);
			SDL_DestroyTexture(textTexture);
		}
	}
}

Key::~Key() {
	if (texture) {
		SDL_DestroyTexture(texture);
	}
}

void Key::timeOfRend(Clock* clock) {
	if (rend) {
		if (!isCounting) {
			startTime = clock->last_tick_time;
			isCounting = true;
		}
		if (clock->last_tick_time - startTime >= 2000) {
			rend = 0;
			isCounting = false;
		}
	} else {
		isCounting = false;
	}
}
