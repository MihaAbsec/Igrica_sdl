#include "include/MainScreen.h"

MainScreen::MainScreen(int width, int height) {
	// Naloži ozadje
	SDL_Surface* tempSurface = IMG_Load("assets/start_menu_background.jpg");
	if (!tempSurface) {
		std::cout << "Error loading menu image: " << IMG_GetError() << std::endl;
	}
	backgroundTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	// Določi pozicijo gumba "Play"
	playButton = {width / 2 - 100, height / 2, 200, 80};
}
/*bool StartMenu::innit() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Error initializing SDL: %s\n", SDL_GetError();
		return false;
	}

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		std::cout << "Error initializing SDL_image: %s\n", IMG_GetError();
		SDL_Quit();
		return false;
	}

	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
	if (!window) {
		std::cout << "Error creating window: %s\n", SDL_GetError();
		SDL_Quit();
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		std::cout << "Error creating renderer: %s\n", SDL_GetError();
		SDL_DestroyWindow(window);
		SDL_Quit();
		return false;
	}

	// Odstranite to vrstico
	// SDL_RenderSetLogicalSize(renderer, original_width, original_height);
	return true;
}*/

MainScreen::~MainScreen() {
	SDL_DestroyTexture(backgroundTexture);
}

void MainScreen::handleEvents(bool& running, bool& startGame) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			running = false;
		}
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

void MainScreen::render() {
	SDL_RenderClear(renderer);

	// Nariši ozadje menija
	SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

	// Nariši "Play" gumb (preprosta zelena škatla)
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &playButton);

	SDL_RenderPresent(renderer);
}
