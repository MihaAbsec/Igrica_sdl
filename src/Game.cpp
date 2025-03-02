#include "include/Game.h"

#include <ctime>
#include <iostream>
#include <vector>

#include "include/Bullet.h"
#include "include/Clock.h"
#include "include/Collision.h"
#include "include/Key.h"
#include "include/Layout1.h"
#include "include/Line.h"
#include "include/Player.h"

// Constructor
Game::Game(int SCREEN_WIDTH, int SCREEN_HEIGHT)
	: SCREEN_WIDTH(SCREEN_WIDTH), SCREEN_HEIGHT(SCREEN_HEIGHT), window(nullptr), renderer(nullptr), player((SCREEN_WIDTH - 50) / 2, (SCREEN_HEIGHT - 50) / 2, 25, 75, 1), running(true), npc(SCREEN_WIDTH - 60, 10, 25, 75, 0.2) {
	// Initialize lines
	layout1 = new Layout1(WORLD_WIDTH, WORLD_HEIGHT);
	key = new Key(SCREEN_WIDTH, SCREEN_HEIGHT, layout1);
	camera = new Camera(player.getX(), player.getY());
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
		mouse.update(event, camera);
	}
}

// Update game logic
void Game::update(Clock* clock) {
	for (Line& line : layout1->lines) {
		collision(player, line);
		for (auto it = bullets.begin(); it != bullets.end();) {
			if (collision(*it, line)) {
				it = bullets.erase(it);
			} else {
				++it;
			}
		}
		if (collision(player, key)) {
			delete key;
			key = new Key(WORLD_WIDTH, WORLD_HEIGHT, layout1);
		}
	}
	player.update(clock);
	npc.movement(clock, layout1, &player);
	npc.update(clock, layout1);
	npc.fov->contact = collision(&player, npc.fov);
	camera->update(&player, WORLD_WIDTH, WORLD_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
	// BULLETS
	static bool wasMousePressed = false;
	static unsigned int last_shot_time = 0;
	if (mouse.getButtons() == 4)
		player.shooting(1);
	if (mouse.getButtons() == 1 || mouse.getButtons() == 5) {
		player.shooting(1);
		if (!wasMousePressed && clock->last_tick_time - last_shot_time >= 250) {
			player.bulletSpawnFix(mouse);
			bullets.push_back(Bullet(player.getGunX(), player.getGunY(), 5, 5, 1, mouse.getWorldX(), mouse.getWorldY()));
			last_shot_time = clock->last_tick_time;
		}
		wasMousePressed = true;
	} else {
		if (clock->last_tick_time - last_shot_time >= 350)
			player.shooting(0);
		wasMousePressed = false;
	}
	for (Bullet& bullets : bullets)
		bullets.update(clock->delta);
}
// Render the game
void Game::render() {
	SDL_SetRenderDrawColor(renderer, 0, 166, 152, 151);	 // background
	SDL_RenderClear(renderer);
	float cameraX = camera->x;
	float cameraY = camera->y;
	for (Line& line : layout1->lines)
		line.render(renderer, cameraX, cameraY);
	for (Bullet& bullets : bullets) {
		bullets.render(renderer, cameraX, cameraY);
	}
	npc.render(renderer, camera);
	player.render(renderer, mouse, SCREEN_WIDTH/2.0, SCREEN_HEIGHT/2.0);
	key->render(renderer, camera);

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
