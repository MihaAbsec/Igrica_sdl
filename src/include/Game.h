#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>

#include <list>
#include <vector>

#include "Bullet.h"
#include "Clock.h"
#include "Line.h"
#include "Mouse.h"
#include "Square.h"

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

	Square player;
	Mouse mouse;
	std::vector<Bullet> bullets;
	std::vector<Line> lines;

	int SCREEN_WIDTH, SCREEN_HEIGHT;
};

#endif	// GAME_H
