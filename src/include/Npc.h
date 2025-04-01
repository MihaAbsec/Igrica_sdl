#ifndef NPC_H
#define NPC_H

#include <SDL2/SDL.h>

#include <cmath>
#include <vector>

#include "Bullet.h"
#include "Camera.h"
#include "Clock.h"
#include "GameObject.h"
#include "NpcFov.h"
#include "Wall.h"

class Npc : public GameObject {
   private:
	// FOR SPRITES
	float gunX, gunY;
    int spawnX = 0, spawnY = 0;
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
	int last_shot_time = 0;
	int headDirection = 2;
	bool hit = false;
	float speed;
	int count = 0;
	bool shooter;

   public:
	friend NpcFov;
	NpcFov* fov;
	void createSprite(SDL_Texture*&, SDL_Renderer*);
	void createSprite();
	void update(Clock*, std::vector<Wall>*);
	void render(SDL_Renderer*, Camera*);
	int getDir() const {
		return headDirection;
	}
	Npc(int, int, int, int, float, std::vector<Wall>*, Game*, Camera*);
	void movement(Clock*, std::vector<Wall>*, Player*, std::vector<Bullet>* bullets);
	bool NpcCollision(std::vector<Wall>*);
	void shooting(Player*, std::vector<Bullet>* bullets, Clock*);
	float getGunX() const {
		if (turn) {
			return x - 18;
		} else {
			return x + sizeWidth + 14;
		}
	}

	float getGunY() const {
		return y + (float)sizeHeight / 2 - 14;
	}
    bool getStatus() const{
        return shooter;
    }
};

#endif
