#ifndef NPC_H
#define NPC_H

#include <SDL2/SDL.h>

#include <cmath>

#include "Clock.h"
#include "GameObject.h"
#include "Layout1.h"

class Npc : public GameObject {
   private:
	int headDirection = 2;
	bool hit = false;
	float speed;

   public:
	int getDir() const {
		return headDirection;
	}
	Npc(float, float, int, int, float);
	void movement(Clock*, Layout1*);
	bool NpcCollision(Layout1*);
};

#endif
