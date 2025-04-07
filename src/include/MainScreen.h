#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>

class MainScreen {
   public:
	MainScreen(int width, int height);
	~MainScreen();
    bool innit();

	void handleEvents(bool& running, bool& startGame);
	void render();

   private:
	SDL_Renderer* renderer;
	SDL_Texture* backgroundTexture;
	SDL_Rect playButton;
};

#endif
