#ifndef KEY_H
#define KEY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_render.h>

#include <vector>

class Game;
#include "Camera.h"
#include "GameObject.h"
#include "Wall.h"
class Key : public GameObject {
	SDL_Texture* texture;
	bool rend = 0;
	bool isCounting = false;
	unsigned int startTime = 0;

   public:
	~Key();
	Key(int width, int height, std::vector<Wall>*, Game*, Camera*);
	bool KeyCollision(std::vector<Wall>*);
	void render(SDL_Renderer* renderer, Camera* camera);
	void nextKey() {
        isCounting = false;
        startTime = 0;
		rend = 1;
	}
	void klicajRender(SDL_Renderer*, Player*, Camera*, TTF_Font*);
	void timeOfRend(Clock*);
};

#endif
