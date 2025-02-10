#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>

#include <vector>

#include "Bullet.h"
#include "Clock.h"
#include "Line.h"
#include "Mouse.h"
#include "Player.h"
#include "Layout1.h"

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

   protected:
	SDL_Window* window;
    
    //Layout1 layout1;
	Player player;
	Mouse mouse;
	std::vector<Bullet> bullets;
    Layout1 *layout1;
	int SCREEN_WIDTH, SCREEN_HEIGHT;
};

#endif	// GAME_H
