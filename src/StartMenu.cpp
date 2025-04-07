#include "include/StartMenu.h"

StartMenu::StartMenu(SDL_Renderer* renderer, int width, int height)
	: renderer(renderer) {
	// Naloži ozadje menija
	SDL_Surface* tempSurface = IMG_Load("assets/menu.png");
	if (!tempSurface) {
		std::cout << "Error loading menu image: " << IMG_GetError() << std::endl;
	}
	backgroundTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	// Nastavi Play gumb
	playButton = {width / 2 - 100, height / 2, 200, 80};
}

StartMenu::~StartMenu() {
	SDL_DestroyTexture(backgroundTexture);
}

void StartMenu::handleEvents(bool& startGame) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			int x, y;
			SDL_GetMouseState(&x, &y);
			if (x >= playButton.x && x <= playButton.x + playButton.w &&
				y >= playButton.y && y <= playButton.y + playButton.h) {
				startGame = true;  // Igra se začne
			}
		}
	}
}

void StartMenu::render() {
	SDL_RenderClear(renderer);

	// Nariši ozadje menija
	SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

	// Nariši "Play" gumb (preprosta zelena škatla)
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &playButton);

	SDL_RenderPresent(renderer);
}

