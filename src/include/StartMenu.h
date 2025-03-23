// StartMenu.h
#ifndef STARTMENU_H
#define STARTMENU_H

#include "SDL2/SDL.h"
#include "SDL_image.h"
#include <string>

class StartMenu {
public:
    StartMenu(SDL_Renderer* renderer, int screenWidth, int screenHeight);
    ~StartMenu();
    void render();
    bool handleEvents(SDL_Event& event);

private:
    SDL_Renderer* renderer;
    SDL_Texture* backgroundTexture;
    SDL_Rect startButtonRect;
    int screenWidth;
    int screenHeight;
};

#endif // STARTMENU_H
