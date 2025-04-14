#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_image.h>

#include <vector>

#include "Bullet.h"
#include "Camera.h"
#include "Clock.h"
#include "Key.h"
#include "Layout1.h"
#include "Map.h"
#include "Mouse.h"
#include "Npc.h"
#include "Player.h"
#include "SDL_rect.h"

class Menu;

enum GameState {
	START_MENU,
	IN_GAME,
	PAUSED,
	GAME_OVER,
	LEVEL_COMPLETE,
    GAME_WINNER
};

class Game {
   public:
	Game(int, int);
	~Game();

	bool init();
	void run();
	void cleanup();
	bool running;

	void render();
	void handleEvents(Clock* clock);
	void update(Clock*);

	SDL_Renderer* renderer;
	static float scale_x;
	static float scale_y;
	int original_width;
	int original_height;
	int SCREEN_WIDTH, SCREEN_HEIGHT;
	const int WORLD_WIDTH = 1920, WORLD_HEIGHT = 1920;

	void setGameState(GameState state);
	GameState getGameState() const;
	bool isRunning() const;
	SDL_Renderer* getRenderer() const;
	void setRunning(bool);
	void renderBGtext();
	void updateLivesText();
	void updateKillsText();
	void updateLevelText();
	void updateKeysText();
	// gamestates
	GameState gameState;

	// leveling
	void loadLevel(int);
	void reset();
	void restart();

   protected:
	SDL_Window* window;
	Player* player;
	Key* key;
	std::vector<Npc>* npc;
	Mouse mouse;
	std::vector<Bullet> bullets;
	std::vector<Wall>* walls;
	Camera* camera;
	Map* map;
	// Besedilo:
	TTF_Font* font;
	std::vector<SDL_Rect>* textBackground = nullptr;
	SDL_Texture* livesTexture = nullptr;
	SDL_Texture* killsTexture = nullptr;
	SDL_Texture* levelTexture = nullptr;
	SDL_Texture* keysTexture = nullptr;
	SDL_Rect livesRect;
	SDL_Rect killsRect;
	SDL_Rect levelRect;
	SDL_Rect keysRect;
	// Leveling
	int keysCollected = 0;
	int currentLevel = 1;
	int lvlKills[4] = {0, 0, 0};
	// Vsi Menuji
	Menu* menu;
};

#endif	// GAME_H
