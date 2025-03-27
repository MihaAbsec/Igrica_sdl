#ifndef GAME_H
#define GAME_H

#include <SDL.h>
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
enum GameState {
	START_MENU,
	IN_GAME
};

class Game {
   public:
	Game(int, int);
	~Game();

	bool innit();
	void run();
	void cleanup();
	bool running;

	void render();
	void handleEvents(Clock* clock);
	void update(Clock*);

	SDL_Renderer* renderer;
	static float scale_x;
	static float scale_y;
	int original_width;	  // Prvotna velikost okna
	int original_height;  // Prvotna velikost okna
	int SCREEN_WIDTH, SCREEN_HEIGHT;
	const int WORLD_WIDTH = 1920, WORLD_HEIGHT = 1920;

	void setGameState(GameState state);
	GameState getGameState() const;
	bool isRunning() const;
	SDL_Renderer* getRenderer() const;
    void setRunning(bool);

   protected:
	SDL_Window* window;

	Player* player;
	Key* key;
	std::vector<Npc> npc;
	Mouse mouse;
	std::vector<Bullet> bullets;
	Layout1* layout1;
    std::vector<Wall> *walls;
	Camera* camera;
	Map* map;
	GameState gameState;
};

#endif	// GAME_H
