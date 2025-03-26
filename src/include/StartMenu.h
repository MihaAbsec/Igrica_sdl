// StartMenu.h
#ifndef STARTMENU_H
#define STARTMENU_H

#include "SDL.h"
#include "SDL_image.h"

class StartMenu {
   public:
	StartMenu(SDL_Renderer* renderer, int screenWidth, int screenHeight);
	~StartMenu();
	bool handleEvents(SDL_Event& event);  // Obdelaj dogodke
	void render();						  // Prikaži meni

   private:
	SDL_Renderer* renderer;
	SDL_Texture* backgroundTexture;	 // Ozadje menija
	SDL_Rect startButtonRect;		 // Območje gumba "Start"
	int screenWidth, screenHeight;
};

#endif	// STARTMENU_H
