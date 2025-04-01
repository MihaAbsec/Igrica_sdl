#ifndef KEY_H
#define KEY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_render.h>
#include <vector>

class Game;
#include "GameObject.h"
#include "Wall.h"
#include "Camera.h"
class Key : public GameObject {
	SDL_Texture* texture;
   public:
    ~Key();
	Key(int width, int height, std::vector<Wall>*, Game*, Camera*);
	bool KeyCollision(std::vector<Wall>*);
	void render(SDL_Renderer* renderer, Camera* camera);
};

#endif
