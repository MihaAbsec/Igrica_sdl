#include "include/Game.h"

#include <ctime>
#include <iostream>
#include <vector>

#include "include/Bullet.h"
#include "include/Clock.h"
#include "include/Collision.h"
#include "include/Layout1.h"
#include "include/Line.h"
#include "include/Player.h"

// Constructor
Game::Game(int SCREEN_WIDTH, int SCREEN_HEIGHT)
	: SCREEN_WIDTH(SCREEN_WIDTH), SCREEN_HEIGHT(SCREEN_HEIGHT), window(nullptr), renderer(nullptr), 
    player((SCREEN_WIDTH - 50) / 2, (SCREEN_HEIGHT - 50) / 2, 30, 50, 1), running(true),
    npc(SCREEN_WIDTH - 60, 10, 50, 50, 0.5){
	// Initialize lines
	layout1 = new Layout1(SCREEN_WIDTH, SCREEN_HEIGHT);
}

// Destructor
Game::~Game() {
	cleanup();
}

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

void Game::handleEvents(Clock* clock) {
	SDL_Event event;
	player.handleInput(event, clock);

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			running = false;
		}
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				running = false;
			}
		}
		mouse.update(event);
	}
}

// Update game logic
void Game::update(Clock* clock) {
	for (Line& line : layout1->lines) {
		collision(player, line);
		int n = 0;
		for (Bullet& bullet : bullets) {
			if (collision(bullet, line)) {
				bullets.erase(bullets.begin() + n);
			}
			n++;
		}
	}
    npc.movement(clock, layout1);
	static bool wasMousePressed = false;
	if (mouse.getButtons() == 1) {
		if (!wasMousePressed && clock->last_tick_time - clock->last_shot_time >= 250) {
			bullets.push_back(Bullet(player.getX() + player.getW() / 2, player.getY() + player.getH() / 2, 5, 5, 1, mouse.getX(), mouse.getY()));
			clock->last_shot_time = clock->last_tick_time;
		}
		wasMousePressed = true;
	} else
		wasMousePressed = false;
	for (Bullet& bullets : bullets)
		bullets.update(clock->delta);
}
// Render the game
void Game::render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);	 // Black background
	SDL_RenderClear(renderer);

	for (Line& line : layout1->lines) 
		line.render(renderer);
	for (Bullet& bullets : bullets) {
		bullets.render(renderer);
	}
    npc.render(renderer);
	player.render(renderer);

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
