#include <SDL.h>
#include <SDL_audio.h>
#include <SDL_keycode.h>
#include <stdio.h>
#include <unistd.h>

#include <iostream>
#include <vector>

#include "include/Detection.h"
#include "include/Line.h"
#include "include/Square.h"
//using namespace std;
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(int argc, char *argv[]) {
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Error initializing SDL: %s\n", SDL_GetError());
		return 1;
	}

	// Create a window
	SDL_Window *window =
		SDL_CreateWindow("Smooth Movement", SDL_WINDOWPOS_CENTERED,
						 SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (window == NULL) {
		printf("Error creating window: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	// Create a renderer
	SDL_Renderer *renderer =
		SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		printf("Error creating renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	// Create a Square object
	Square square((SCREEN_WIDTH - 50) / 2, (SCREEN_HEIGHT - 50) / 2, 50, 5);
    std::vector<Line> lines = {
        Line(0, 0, 0, SCREEN_HEIGHT),
        Line(SCREEN_WIDTH, 0, 0, SCREEN_HEIGHT),
        Line(0, 0, SCREEN_WIDTH, 0),
        Line(0, SCREEN_HEIGHT, SCREEN_WIDTH, 0),
        Line((SCREEN_WIDTH+300)/2, (SCREEN_HEIGHT+300)/2, 50, 50),
        Line((SCREEN_WIDTH - 400) / 2, (SCREEN_HEIGHT) / 2, 1, 200),
        Line((SCREEN_WIDTH - 400) / 2, (SCREEN_HEIGHT) / 2, 200, 1),
        Line((SCREEN_WIDTH) / 2, (SCREEN_HEIGHT - 400) / 2, 1, 200)
    };

	Detection *detection;

	// Main loop
	int running = 1;
	SDL_Event event;
	while (running) {
		// Handle events (e.g., window close)
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = 0;
			}
			if (event.type == SDL_KEYDOWN)
				if (event.key.keysym.sym == SDLK_ESCAPE)
					running = 0;
		}

		square.handleInput(event);
		// detection->contact(square, line);

		// Clear screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);	 // Black background
		SDL_RenderClear(renderer);

		// Render the square
        for(Line line : lines){
            square.update(line);
            line.render(renderer);
        }
		square.render(renderer);
		// cout << "OLD: " << square.getoldX() << " " << square.getoldY() << endl;
        std::cout << square.getX() << " " << square.getY() << '\r';
        std::cout.flush();
		// Update screen
		SDL_RenderPresent(renderer);

		// Cap the frame rate
		SDL_Delay(16);	// ~60 FPS
	}

	// Clean up
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
