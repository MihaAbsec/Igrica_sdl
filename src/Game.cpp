#include "include/Game.h"

#include <SDL2/SDL_ttf.h>

#include <algorithm>
#include <cmath>
#include <ctime>
#include <filesystem>
#include <format>
#include <iostream>
#include <string>
#include <vector>

#include "SDL_rect.h"
#include "SDL_surface.h"
#include "include/Bullet.h"
#include "include/Clock.h"
#include "include/Collision.h"
#include "include/GameObject.h"
#include "include/Key.h"
#include "include/Menu.h"
#include "include/Player.h"
#include "include/Wall.h"
float Game::scale_x = 1.0f;
float Game::scale_y = 1.0f;
Game::Game(int SCREEN_WIDTH, int SCREEN_HEIGHT)
	: SCREEN_WIDTH(SCREEN_WIDTH), SCREEN_HEIGHT(SCREEN_HEIGHT), window(nullptr), renderer(nullptr), running(true) {
	original_height = SCREEN_HEIGHT;
	original_width = SCREEN_WIDTH;
	player = new Player(192, 192, 25, 75, 1);
	camera = new Camera(player->getX(), player->getY());
	camera->update(player, WORLD_WIDTH, WORLD_HEIGHT, original_width, original_height);
	walls = new std::vector<Wall>();
	npc = new std::vector<Npc>();
	textBackground = new std::vector<SDL_Rect>;
	gameState = START_MENU;
	replay = new Replay(1);
	saving = new Saving();
}

Game::~Game() {
	cleanup();
}

bool Game::init() {
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
	if (TTF_Init() == -1) {
		std::cout << "Failed to initialize SDL_ttf: " << TTF_GetError() << "\n";
		return false;
	}

	font = TTF_OpenFont("assets/fonts/pisava.ttf", 32);
	if (!font) {
		std::cout << "Failed to load font: " << TTF_GetError() << "\n";
		return false;
	}

	map = new Map("assets/floor.png", "assets/wall1.png", "maps/level1.txt", renderer, walls);
	key = new Key(SCREEN_WIDTH, SCREEN_HEIGHT, walls, this, camera);
	for (int i = 0; i < 14; ++i)
		npc->push_back(Npc(WORLD_WIDTH, WORLD_HEIGHT, 25, 75, 0.2, walls, this, camera));
	menu = new Menu(font);
	return true;
}

void Game::handleEvents(Clock* clock) {
	SDL_Event event;
	if (gameState == IN_GAME) {
		player->handleInput(event, clock, replay, key);
	} else if (gameState == PAUSED)
		menu->handleEvent_Paused(event, &mouse, this);
	else if (gameState == START_MENU)
		menu->handleEvent_StartMenu(event, &mouse, this);
	else if (gameState == GAME_OVER)
		menu->handleEvent_GameOver(event, &mouse, this);
	else if (gameState == LEVEL_COMPLETE)
		menu->handleEvent_LevelComplete(event, &mouse, this);
	else if (gameState == GAME_WINNER)
		menu->handleEvent_GameWinner(event, &mouse, this);

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			running = false;
		}
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_ESCAPE && gameState == IN_GAME)
				gameState = PAUSED;
			else if (event.key.keysym.sym == SDLK_ESCAPE && gameState == PAUSED)
				gameState = IN_GAME;
			else if (event.key.keysym.sym == SDLK_ESCAPE && gameState == REPLAY_MODE)
				gameState = prevGameState;
		}
		if (event.type == SDL_WINDOWEVENT) {
			if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
				SCREEN_WIDTH = event.window.data1;
				SCREEN_HEIGHT = event.window.data2;

				int desiredHeight = (int)(SCREEN_WIDTH * 9 / 16);
				if (SCREEN_HEIGHT != desiredHeight) {
					SDL_SetWindowSize(window, SCREEN_WIDTH, desiredHeight);
					SCREEN_HEIGHT = desiredHeight;
				}

				scale_x = (float)SCREEN_WIDTH / original_width;
				scale_y = (float)SCREEN_HEIGHT / original_height;

				// std::cout << "Window resized to: " << SCREEN_WIDTH << "x" << SCREEN_HEIGHT << std::endl;
				// std::cout << "Scale factor: " << scale_x << ", " << scale_y << std::endl;
			}
		}
		mouse.update(event, camera);
	}
}

void Game::update(Clock* clock) {
	if (gameState == IN_GAME) {
		gameTimer(clock);
		replay->setLvl(currentLevel);
		if (!player->getLives()) {
			currentLevel++;
			gameState = GAME_OVER;
			if (fromSaving) {
				saving->emptyFile();
			}
		} else if (fromSaving) {
			saveProgressFromMenu();
		}
		for (Wall& wall : *walls) {
			collision(*player, wall);
			for (auto it = bullets.begin(); it != bullets.end();) {
				if (collision(&(*it), &wall)) {
					it = bullets.erase(it);
				} else {
					++it;
				}
			}
		}
		auto itB = bullets.begin();
		while (itB != bullets.end()) {
			bool bulletErased = false;
			auto it = npc->begin();
			if (collision(&(*itB), player)) {
				player->hit();
				itB = bullets.erase(itB);
				bulletErased = true;
			}
			while (it != npc->end() && !bulletErased) {
				if (collision(&(*itB), &(*it))) {
					it = npc->erase(it);
					player->plusKill();
					npc->push_back(Npc(WORLD_WIDTH, WORLD_HEIGHT, 25, 75, 0.2, walls, this, camera));
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

		// ključi in leveli
		key->timeOfRend(clock);
		if (collision(player, key)) {
			keysCollected++;
			delete key;
			key = new Key(WORLD_WIDTH, WORLD_HEIGHT, walls, this, camera);
			if (keysCollected >= 3) {
				lvlKills[currentLevel] = player->getKills();
				lvlTimer[currentLevel] = timer;
				if (player->getLives())
					currentLevel++;
				if (currentLevel > 3) {
					currentLevel--;
					gameState = GAME_WINNER;
				} else
					gameState = LEVEL_COMPLETE;
				player->setKills(lvlKills[currentLevel - 1]);
			} else {
				key->nextKey();
			}
		}
		player->update(clock);
		for (Npc& npcs : *npc) {
			npcs.movement(clock, walls, player, &bullets);
			npcs.update(clock, walls);
			npcs.fov->contact = collision(player, npcs.fov);
			collision(&npcs, player);
			if (collision(player, &npcs))
				player->die();
			for (Npc& npcs_ : *npc) {
				if (&npcs != &npcs_)
					collision(&npcs, &npcs_);
			}
		}
		camera->update(player, WORLD_WIDTH, WORLD_HEIGHT, original_width, original_height);
		// BULLETS  streljanje
		static bool wasMousePressed = false;
		static unsigned int last_shot_time = 0;
		if (mouse.getButtons() == 4)
			player->shooting(1);
		if (mouse.getButtons() == 1 || mouse.getButtons() == 5) {
			player->shooting(1);
			if (!wasMousePressed && clock->gameTimer - last_shot_time >= 250) {
				player->bulletSpawnFix(mouse);
				bullets.push_back(Bullet(1, player->getGunX(), player->getGunY(), 5, 5, 1, mouse.getWorldX(), mouse.getWorldY()));
				last_shot_time = clock->gameTimer;
			}
			wasMousePressed = true;
		} else {
			if (clock->gameTimer - last_shot_time >= 350)
				player->shooting(0);
			wasMousePressed = false;
		}
		for (Bullet& bullets : bullets)
			bullets.update(clock->delta);
		textBackground->clear();
		updateLivesText();
		updateKillsText();
		updateLevelText();
		updateKeysText();
		updateTimerText(clock);
	} else
		pausedTime = clock->last_tick_time - timer;
	if (gameState == REPLAY_MODE) {
		player->replayMovement(replay, clock, this);
		camera->update(player, WORLD_WIDTH, WORLD_HEIGHT, original_width, original_height);
		key->replayCoordinates(replay, clock, this);
	}
}
// Render
void Game::render() {
	SDL_RenderClear(renderer);

	SDL_RenderSetScale(renderer, scale_x, scale_y);
	if (gameState == START_MENU) {
		menu->startMenuRender(renderer, this);
	} else if (gameState != REPLAY_MODE) {
		map->render(renderer, camera);
		float cameraX = camera->x;
		float cameraY = camera->y;
		for (Bullet& bullet : bullets)
			bullet.render(renderer, cameraX, cameraY);
		for (Npc& npc : *npc)
			npc.render(renderer, camera);
		if (player->radious->isContact(player, key, walls))
			key->render(renderer, camera);
		key->klicajRender(renderer, player, camera, font);
		renderBGtext();
		SDL_RenderCopy(renderer, livesTexture, NULL, &livesRect);
		SDL_RenderCopy(renderer, killsTexture, NULL, &killsRect);
		SDL_RenderCopy(renderer, levelTexture, NULL, &levelRect);
		SDL_RenderCopy(renderer, keysTexture, NULL, &keysRect);
		SDL_RenderCopy(renderer, timerTexture, NULL, &timerRect);
		if (gameState == GAME_OVER)
			menu->gameOverMenu(renderer, this);
		if (gameState == LEVEL_COMPLETE)
			menu->levelCompleteMenu(renderer, this);
		if (gameState == GAME_WINNER)
			menu->gameWinnerMenu(renderer, this);
		player->render(renderer, mouse, original_width / 2.0, original_height / 2.0, camera, this);
		if (gameState == PAUSED)
			menu->pausedRender(renderer, this);
	}
	if (gameState == REPLAY_MODE) {
		map->render(renderer, camera);
		float cameraX = camera->x;
		float cameraY = camera->y;
		player->render(renderer, mouse, original_width / 2.0, original_height / 2.0, camera, this);
		key->render(renderer, camera);
	}

	SDL_RenderPresent(renderer);
}
void Game::cleanup() {
	delete npc;
	delete player;
	delete walls;
	delete replay;

	if (livesTexture) {
		SDL_DestroyTexture(livesTexture);
		livesTexture = nullptr;
	}
	if (killsTexture) {
		SDL_DestroyTexture(killsTexture);
		killsTexture = nullptr;
	}
	if (keysTexture) {
		SDL_DestroyTexture(keysTexture);
		keysTexture = nullptr;
	}
	if (map) {
		delete map;
		map = nullptr;
	}
	if (menu) {
		delete menu;
		menu = nullptr;
	}

	if (font) {
		TTF_CloseFont(font);
		font = nullptr;
	}

	if (textBackground) {
		delete textBackground;
		textBackground = nullptr;
	}

	if (renderer) {
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}
	if (window) {
		SDL_DestroyWindow(window);
		window = nullptr;
	}
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

bool Game::isRunning() const {
	return running;
}

SDL_Renderer* Game::getRenderer() const {
	return renderer;
}
void Game::setRunning(bool running) {
	this->running = running;
}

void Game::updateLivesText() {
	if (livesTexture) {
		SDL_DestroyTexture(livesTexture);
		livesTexture = nullptr;
	}

	SDL_Color color = {255, 50, 50};
	std::string text = " ";
	for (int i = 0; i < player->getLives(); i++)
		text += "_ ";
	SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
	if (!surface) {
		std::cout << "Failed to render text surface: " << TTF_GetError() << "\n";
		return;
	}

	livesTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if (!livesTexture) {
		std::cout << "Failed to create text texture: " << SDL_GetError() << "\n";
		SDL_FreeSurface(surface);
		return;
	}

	livesRect = {8, 0,
				 static_cast<int>(surface->w * 1.5),
				 static_cast<int>(surface->h * 1.5)};
	SDL_Rect rect = {8, 8, 132, surface->h + 4};
	textBackground->push_back(rect);
}
void Game::updateKillsText() {
	if (killsTexture) {
		SDL_DestroyTexture(killsTexture);
		killsTexture = nullptr;
	}

	SDL_Color color = {255, 255, 255};
	std::string text = "€   " + std::to_string(player->getKills());
	SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
	if (!surface) {
		std::cout << "Failed to render text surface: " << TTF_GetError() << "\n";
		return;
	}

	killsTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if (!killsTexture) {
		std::cout << "Failed to create text texture: " << SDL_GetError() << "\n";
		SDL_FreeSurface(surface);
		return;
	}

	killsRect = {26, 40, surface->w, surface->h};
	SDL_Rect rect = {8, 38, static_cast<int>(surface->w * 1.5), surface->h + 4};
	textBackground->push_back(rect);
}
void Game::updateLevelText() {
	if (levelTexture) {
		SDL_DestroyTexture(levelTexture);
		levelTexture = nullptr;
	}

	SDL_Color color = {255, 255, 255};
	std::string text = "Level: " + std::to_string(currentLevel) + "/3";
	SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
	if (!surface) {
		std::cout << "Failed to render text surface: " << TTF_GetError() << "\n";
		return;
	}

	levelTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if (!levelTexture) {
		std::cout << "Failed to create text texture: " << SDL_GetError() << "\n";
		SDL_FreeSurface(surface);
		return;
	}

	levelRect = {original_width / 2 - surface->w / 2, 10, surface->w, surface->h};	// zgornji levi kot
	SDL_Rect rect = {original_width / 2 - surface->w / 2 - 3, 10, surface->w + 4, surface->h + 4};

	textBackground->push_back(rect);
}

void Game::updateKeysText() {
	if (keysTexture) {
		SDL_DestroyTexture(keysTexture);
		keysTexture = nullptr;
	}

	SDL_Color color = {212, 175, 55};
	std::string text = " ";
	for (int i = 0; i < keysCollected; i++) {
		text += "© ";
	}
	SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
	if (!surface) {
		std::cout << "Failed to render text surface: " << TTF_GetError() << "\n";
		return;
	}

	keysTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if (!keysTexture) {
		std::cout << "Failed to create text texture: " << SDL_GetError() << "\n";
		SDL_FreeSurface(surface);
		return;
	}

	keysRect = {11, original_height - surface->h - 18,
				static_cast<int>(surface->w * 1.5),
				static_cast<int>(surface->h * 1.5)};
	SDL_Rect rect = {10, original_height - 10 - surface->h,
					 static_cast<int>(surface->w * 1.5), surface->h + 4};

	textBackground->push_back(rect);
}
void Game::updateTimerText(Clock* clock) {
	if (timerTexture) {
		SDL_DestroyTexture(timerTexture);
		timerTexture = nullptr;
	}

	SDL_Color color = {255, 255, 255};
	int a = timer / 1000;
	int b = (timer - a * 1000) / 100;
	std::string text = std::to_string(a) + "." + std::to_string(b);
	SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
	if (!surface) {
		std::cout << "Failed to render text surface: " << TTF_GetError() << "\n";
		return;
	}

	timerTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if (!timerTexture) {
		std::cout << "Failed to create text texture: " << SDL_GetError() << "\n";
		SDL_FreeSurface(surface);
		return;
	}

	timerRect = {original_width - 100, 10,
				 static_cast<int>(surface->w),
				 static_cast<int>(surface->h)};
	SDL_Rect rect = {10, original_height - 10 - surface->h,
					 static_cast<int>(surface->w), surface->h + 4};

	textBackground->push_back(timerRect);
}

void Game::renderBGtext() {
	for (SDL_Rect& bc : *textBackground) {
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
		SDL_RenderFillRect(renderer, &bc);
	}
}

void Game::loadLevel(int level, bool isSave) {
	keysCollected = 0;
	walls->clear();
	npc->clear();

	std::string levelFile = "maps/level" + std::to_string(level) + ".txt";
	std::string levelWall = "assets/wall" + std::to_string(level) + ".png";
	delete map;	 // Izbriši staro mapo
	map = new Map("assets/floor.png", levelWall, levelFile, renderer, walls);

	if (isSave == false) {
		delete player;
		player = new Player(192, 192, 25, 75, 1);
	}
	camera->update(player, WORLD_WIDTH, WORLD_HEIGHT, original_width, original_height);

	for (int i = 0; i < 14; ++i) {
		npc->push_back(Npc(WORLD_WIDTH, WORLD_HEIGHT, 25, 75, 0.2, walls, this, camera));
	}

	delete key;
	key = new Key(WORLD_WIDTH, WORLD_HEIGHT, walls, this, camera);
}

void Game::reset() {
	fromSaving = 0;
	player->setKills(0);
	lvlKills[1] = 0;
	lvlKills[2] = 0;
	lvlKills[3] = 0;
	currentLevel = 1;
	setTimer = 1;
	emptyReplay();
	loadLevel(currentLevel, false);
}

void Game::restart() {
	loadLevel(currentLevel, false);
	player->setKills(lvlKills[currentLevel - 1]);
	replay->emptyFile(currentLevel);
	setTimer = lvlTimer[currentLevel - 1];
}
void Game::gameTimer(Clock* clock) {
	if (setTimer != -1) {
		timer = setTimer;
		clock->gameTimer = setTimer;
		pausedTime = clock->last_tick_time - setTimer;
		setTimer = -1;
	} else {
		timer = clock->last_tick_time - pausedTime;
		clock->gameTimer = timer;
	}
}

void Game::setGameFromSaveing() {
	fromSaving = 1;
	Progress a = saving->getProgress();
	currentLevel = a.currentLevel;
	player->setPosition(a.x, a.y);
	loadLevel(currentLevel, true);
	player->setKills(a.kills);
	setTimer = a.time;
	keysCollected = a.keys;
	player->setLives(a.lives);
	lvlKills[currentLevel - 1] = a.prevKills;
	lvlTimer[currentLevel - 1] = a.prevTime;
}

void Game::saveProgressFromMenu() {
	saving->saveProgress(this, player);
}

void Game::emptyReplay() {
	for (int i = 1; i <= 3; i++)
		replay->emptyFile(i);
}
void Game::emptySaving() {
	saving->emptyFile();
}

bool Game::isSavingEmpty() {
	return saving->isFileEmpty();
}
