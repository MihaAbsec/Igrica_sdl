#ifndef NPC_H
#define NPC_H

#include <SDL2/SDL.h>

#include <cmath>

#include "Camera.h"
#include "Clock.h"
#include "GameObject.h"
#include "Layout1.h"
#include "NpcFov.h"

class Npc : public GameObject {
   private:
	// FOR SPRITES
	float gunX, gunY;
	int move;
	bool turn = 0;
	SDL_Texture* officer;
	SDL_Rect idleFrame;
	std::vector<SDL_Rect> walkFrames;
	std::vector<SDL_Rect> runFrames;
	std::vector<SDL_Rect> shootFrames;
	int currentFrameRun;
	int currentFrameShoot;
	int currentFrameWalk;
	Uint32 lastFrameTime;

	int last_npc_time = 0;
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
	Npc(int, int, int, int, float, Layout1*);
	void movement(Clock*, Layout1*, Player*);
	bool NpcCollision(Layout1*);
};

#endif
