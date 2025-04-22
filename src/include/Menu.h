#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

#include <string>
#include <vector>

#include "Game.h"

class Menu {
   public:
	Menu(TTF_Font* font);
	~Menu();

	void pausedRender(SDL_Renderer*, Game*);
	void startMenuRender(SDL_Renderer*, Game*);
	void gameOverMenu(SDL_Renderer*, Game*);
	void levelCompleteMenu(SDL_Renderer*, Game*);
	void gameWinnerMenu(SDL_Renderer*, Game*);
	void handleEvent_Paused(SDL_Event& event, Mouse* mouse, Game*);
	void handleEvent_StartMenu(SDL_Event& event, Mouse* mouse, Game*);
	void handleEvent_GameOver(SDL_Event& event, Mouse* mouse, Game*);
	void handleEvent_LevelComplete(SDL_Event& event, Mouse* mouse, Game*);
	void handleEvent_GameWinner(SDL_Event& event, Mouse* mouse, Game*);
	void addButton(SDL_Renderer*, const std::string& text, SDL_Rect rect);

   private:
	// SDL_Renderer* renderer;
	SDL_Texture* backgroundTexture = nullptr;
	TTF_Font* font;
	std::vector<SDL_Texture*> buttonTextures;
	std::vector<SDL_Rect> buttonRects;
	std::vector<bool> interakcija = {0};
	bool replayButton = 0;
};
