#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>

#include <vector>

#include "Bullet.h"
#include "Clock.h"
#include "Key.h"
#include "Layout1.h"
#include "Line.h"
#include "Mouse.h"
#include "Npc.h"
#include "Player.h"
#include "Camera.h"

class Game {
   public:
	Game(int, int);
	~Game();

	bool innit();
	void run();
	void cleanup();
	bool running;

	void render();
	void handleEvents(Clock*);
	void update(Clock*);

	SDL_Renderer* renderer;
    
	const int SCREEN_WIDTH, SCREEN_HEIGHT;
    const float WORLD_WIDTH = 2000, WORLD_HEIGHT = 2000;

   protected:
	SDL_Window* window;

	// Layout1 layout1;
	Player player;
	Key* key;
	Npc npc;
	Mouse mouse;
	std::vector<Bullet> bullets;
	Layout1* layout1;
    Camera* camera;
};

#endif	// GAME_H
