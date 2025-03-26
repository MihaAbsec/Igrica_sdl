#include "include/Game.h"

#include <ctime>
#include <filesystem>
#include <iostream>
#include <vector>

#include "include/Bullet.h"
#include "include/Clock.h"
#include "include/Collision.h"
#include "include/Key.h"
#include "include/Layout1.h"
#include "include/Wall.h"
#include "include/Player.h"
float Game::scale_x = 1.0f;
float Game::scale_y = 1.0f;
Game::Game(int SCREEN_WIDTH, int SCREEN_HEIGHT)
	: SCREEN_WIDTH(SCREEN_WIDTH), SCREEN_HEIGHT(SCREEN_HEIGHT), window(nullptr), renderer(nullptr), running(true) {
	original_height = SCREEN_HEIGHT;
	original_width = SCREEN_WIDTH;
	player = new Player((SCREEN_WIDTH - 50) / 2, (SCREEN_HEIGHT - 50) / 2, 25, 75, 1);
	layout1 = new Layout1(WORLD_WIDTH, WORLD_HEIGHT);
	key = new Key(SCREEN_WIDTH, SCREEN_HEIGHT, layout1);
	camera = new Camera(player->getX(), player->getY());
	for (int i = 0; i < 7; ++i)
		npc.push_back(Npc(WORLD_WIDTH, WORLD_HEIGHT, 25, 75, 0.2, layout1));
	// map = new Map("assets/floor.png", "assets/wall.png", "maps/level1.txt", renderer);
}

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
	map = new Map("assets/floor.png", "assets/wall.png", "maps/level1.txt", renderer);
	return true;
}

// V Game.cpp
void Game::handleEvents(Clock* clock) {
	SDL_Event event;
	player->handleInput(event, clock);

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			running = false;
		}
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				running = false;
			}
		}
		if (event.type == SDL_WINDOWEVENT) {
			if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
				// Posodobi velikost okna
				SCREEN_WIDTH = event.window.data1;
				SCREEN_HEIGHT = event.window.data2;

				// Izračunaj želeno višino glede na širino (ohrani razmerje stranic 16:9)
				int desiredHeight = (int)(SCREEN_WIDTH * 9 / 16);
				if (SCREEN_HEIGHT != desiredHeight) {
					// Če višina ni pravilna, prilagodi velikost okna
					SDL_SetWindowSize(window, SCREEN_WIDTH, desiredHeight);
					SCREEN_HEIGHT = desiredHeight;
				}

				// Izračunaj scale faktor
				scale_x = (float)SCREEN_WIDTH / original_width;
				scale_y = (float)SCREEN_HEIGHT / original_height;

				std::cout << "Window resized to: " << SCREEN_WIDTH << "x" << SCREEN_HEIGHT << std::endl;
				std::cout << "Scale factor: " << scale_x << ", " << scale_y << std::endl;
			}
		}
		mouse.update(event, camera);
	}
}

// Update game logic

void Game::update(Clock* clock) {
	for (Wall& line : layout1->lines) {
		collision(*player, line);
		for (auto it = bullets.begin(); it != bullets.end();) {
			if (collision(&(*it), &line)) {
				it = bullets.erase(it);
			} else {
				++it;
			}
		}
	}
	auto itB = bullets.begin();
	while (itB != bullets.end()) {
		bool bulletErased = false;
		auto it = npc.begin();
		while (it != npc.end()) {
			if (collision(&(*itB), &(*it))) {
				it = npc.erase(it);
				itB = bullets.erase(itB);
				bulletErased = true;
				break;
			} else {
				++it;
			}
		}
		if (!bulletErased) {
			++itB;
		}
	}
	if (collision(player, key)) {
		delete key;
		key = new Key(WORLD_WIDTH, WORLD_HEIGHT, layout1);
	}
	player->update(clock);
	for (Npc& npcs : npc) {
		npcs.movement(clock, layout1, player);
		npcs.update(clock, layout1);
		npcs.fov->contact = collision(player, npcs.fov);
		for (Npc& npcs_ : npc) {
			if (&npcs != &npcs_)
				collision(&npcs, &npcs_);
		}
	}
	camera->update(player, WORLD_WIDTH, WORLD_HEIGHT, original_width, original_height);
	// BULLETS
	static bool wasMousePressed = false;
	static unsigned int last_shot_time = 0;
	if (mouse.getButtons() == 4)
		player->shooting(1);
	if (mouse.getButtons() == 1 || mouse.getButtons() == 5) {
		player->shooting(1);
		if (!wasMousePressed && clock->last_tick_time - last_shot_time >= 250) {
			player->bulletSpawnFix(mouse);
			bullets.push_back(Bullet(player->getGunX(), player->getGunY(), 5, 5, 1, mouse.getWorldX(), mouse.getWorldY()));
			last_shot_time = clock->last_tick_time;
		}
		wasMousePressed = true;
	} else {
		if (clock->last_tick_time - last_shot_time >= 350)
			player->shooting(0);
		wasMousePressed = false;
	}
	for (Bullet& bullets : bullets)
		bullets.update(clock->delta);
}
// Render
void Game::render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);	 // Črna barva za ozadje
	SDL_RenderClear(renderer);

	// Nastavi skaliranje na rendererju
	SDL_RenderSetScale(renderer, scale_x, scale_y);

	// Risanje objektov
	map->render(renderer, camera);
	float cameraX = camera->x;
	float cameraY = camera->y;
	for (Wall& line : layout1->lines)
		line.render(renderer, cameraX, cameraY);
	for (Bullet& bullet : bullets)
		bullet.render(renderer, cameraX, cameraY);
	for (Npc& npc : npc)
		npc.render(renderer, camera);
	player->render(renderer, mouse, original_width / 2.0, original_height / 2.0, camera);
	key->render(renderer, camera);

	SDL_RenderPresent(renderer);
}
// cleanup
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

void Game::setGameState(GameState state) {
	gameState = state;
}

GameState Game::getGameState() const {
	return gameState;
}

bool Game::isRunning() const {
	return running;
}

SDL_Renderer* Game::getRenderer() const {
	return renderer;
}
void Game::setRunning(bool running) {
	this->running = running;
	std::cout << "Game running state set to: " << running << std::endl;
}
