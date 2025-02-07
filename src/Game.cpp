#include "include/Game.h"

#include <iostream>
#include <vector>

#include "include/Line.h"
#include "include/Square.h"
#include "include/Collision.h"

// Constructor
Game::Game(int SCREEN_WIDTH, int SCREEN_HEIGHT)
	: SCREEN_WIDTH(SCREEN_WIDTH), SCREEN_HEIGHT(SCREEN_HEIGHT), window(nullptr), renderer(nullptr), square((SCREEN_WIDTH - 50) / 2, (SCREEN_HEIGHT - 50) / 2, 30, 50, 5), running(true) {
	// Initialize lines
	lines = {
		Line(0, 0, 0, SCREEN_HEIGHT),										// Left wall
		Line(SCREEN_WIDTH, 0, 0, SCREEN_HEIGHT),							// Right wall
		Line(0, 0, SCREEN_WIDTH, 0),										// Top wall
		Line(0, SCREEN_HEIGHT, SCREEN_WIDTH, 0),							// Bottom wall
		Line((SCREEN_WIDTH + 300) / 2, (SCREEN_HEIGHT + 300) / 2, 50, 50),	// Obstacle
		Line((SCREEN_WIDTH - 400) / 2, (SCREEN_HEIGHT) / 2, 1, 200),		// Vertical line
		Line((SCREEN_WIDTH - 400) / 2, (SCREEN_HEIGHT) / 2, 200, 1),		// Horizontal line
		Line((SCREEN_WIDTH) / 2, (SCREEN_HEIGHT - 400) / 2, 1, 200)			// Vertical line
	};
}

// Destructor
Game::~Game() {
	cleanup();
}

// Initialize SDL, window, renderer, etc.
bool Game::innit() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Error initializing SDL: %s\n", SDL_GetError();
		return false;
	}

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		std::cout << "Error initializing SDL_image: %s\n", IMG_GetError();
		SDL_Quit();
		return false;
	}

	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
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

	return true;
}

// Handle SDL events (e.g., keyboard input)
void Game::handleEvents() {
	SDL_Event event;
	square.handleInput(event);

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			running = false;
		}
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				running = false;
			}
		}
	}
}

// Update game logic
void Game::update() {
	for (Line& line : lines) {
		collision(square, line);
        square.update(line);
	}
}

// Render the game
void Game::render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);	 // Black background
	SDL_RenderClear(renderer);

	for (Line& line : lines) {
		line.render(renderer);
	}
	square.render(renderer);

	SDL_RenderPresent(renderer);
}

// Clean up resources
void Game::cleanup() {
	if (renderer) {
		SDL_DestroyRenderer(renderer);
	}
	if (window) {
		SDL_DestroyWindow(window);
	}
	IMG_Quit();
	SDL_Quit();
}
