#ifndef NPC_H
#define NPC_H

#include <SDL2/SDL.h>

#include <cmath>

#include "Clock.h"
#include "GameObject.h"
#include "Layout1.h"
#include "NpcFov.h"
#include "Camera.h"

class Npc : public GameObject {
   private:
	// FOR SPRITES
	float gunX, gunY;
	int move;
	bool turn;
	SDL_Texture* officer;
	SDL_Rect idleFrame;
	std::vector<SDL_Rect> walkFrames;
	std::vector<SDL_Rect> runFrames;
	std::vector<SDL_Rect> shootFrames;
	int currentFrameRun;
	int currentFrameShoot;
	int currentFrameWalk;
	Uint32 lastFrameTime;

	int headDirection = 2;
	bool hit = false;
	float speed;

   public:
	friend NpcFov;
	NpcFov* fov;
	void createSprite(SDL_Texture*&, SDL_Renderer*);
	void createSprite();
	void update(Clock*, Layout1*);
	void render(SDL_Renderer*, Camera*);
	int getDir() const {
		return headDirection;
	}
	Npc(float, float, int, int, float);
	void movement(Clock*, Layout1*, Player*);
	bool NpcCollision(Layout1*);
};

#endif
