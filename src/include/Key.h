#ifndef KEY_H
#define KEY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_render.h>

#include "GameObject.h"
#include "Layout1.h"
class Key : public GameObject {
	SDL_Texture* texture;
   public:
    ~Key();
	Key(int width, int height, Layout1*);
	bool KeyCollision(Layout1*);
	void render(SDL_Renderer* renderer);
};

#endif
