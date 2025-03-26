// StartMenu.cpp
#include "include/StartMenu.h"
#include <iostream>

StartMenu::StartMenu(SDL_Renderer* renderer, int screenWidth, int screenHeight)
	: renderer(renderer), screenWidth(screenWidth), screenHeight(screenHeight) {
	// Naloži ozadje
	backgroundTexture = IMG_LoadTexture(renderer, "assets/start_menu_background.jpg");
	if (!backgroundTexture) {
		std::cerr << "Failed to load background texture: " << IMG_GetError() << std::endl;
	}

	// Nastavi območje gumba "Start"
	startButtonRect = {screenWidth / 2 - 100, screenHeight / 2 - 50, 200, 100};
}

StartMenu::~StartMenu() {
	if (backgroundTexture) {
		SDL_DestroyTexture(backgroundTexture);
	}
}

bool StartMenu::handleEvents(SDL_Event& event) {
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		if (x >= startButtonRect.x && x <= startButtonRect.x + startButtonRect.w &&
			y >= startButtonRect.y && y <= startButtonRect.y + startButtonRect.h) {
			return true;  // Kliknili smo na gumb "Start"
		}
	}
	return false;
}

void StartMenu::render() {
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);  // Prikaži ozadje

	// Nariši gumb "Start"
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  // Zelena barva
	SDL_RenderFillRect(renderer, &startButtonRect);

	SDL_RenderPresent(renderer);
}
