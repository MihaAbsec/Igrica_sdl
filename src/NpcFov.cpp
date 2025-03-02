#include "include/NpcFov.h"

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <iostream>

#include "include/Clock.h"
#include "include/Collision.h"
#include "include/Layout1.h"
#include "include/Npc.h"
#include "include/NpcFov.h"
#include "include/Player.h"

void NpcFov::update(Npc* npc, Layout1* layout) {
	if (!npc->turn)
		x = npc->x - 12.5;
	else
		x = npc->x - width + npc->sizeWidth + 12.5;
	y = (npc->y + npc->sizeHeight / 2) - height / 2;
	/*for (Line line : layout->lines)
		FovLineCollision(this, &line);*/
}
void NpcFov::isContact(Npc* npc, Player* player, Clock* clock, Layout1* layout) {
	if (lineIntersectsWall(npc->x, npc->y, player->x + 5, player->y + 5, layout)) {
		contact = 0;
		return;	 
	}
	access = 0;
	npc->move = 2;
	float speed = npc->speed * 1.3;

	glm::vec2 position(npc->x, npc->y);
	glm::vec2 target(player->x, player->y);
	glm::vec2 direction = target - position;

	float length = glm::length(direction);
	if (length != 0) {
		direction = glm::normalize(direction);
	} else {
		direction = glm::vec2(0, 0);
		npc->turn = 0;
	}

	npc->oldX = npc->x;
	npc->oldY = npc->y;
	npc->x += direction.x * speed * clock->delta;
	npc->y += direction.y * speed * clock->delta;
	npc->turn = (player->x < npc->x) ? 1 : 0;
}

void NpcFov::render(SDL_Renderer* renderer, Camera* camera) {
	SDL_Rect rect = {static_cast<int>(x - camera->x),
					 static_cast<int>(y - camera->y), width, height};
	SDL_SetRenderDrawColor(renderer, 0, 173, 198, 240);
	SDL_RenderFillRect(renderer, &rect);
}
