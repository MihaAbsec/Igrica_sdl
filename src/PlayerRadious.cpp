#include "include/PlayerRadious.h"

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <iostream>

#include "SDL_render.h"
#include "include/Clock.h"
#include "include/Collision.h"
#include "include/Npc.h"
#include "include/NpcFov.h"
#include "include/Player.h"

void PlayerRadious::update(Player* player) {
	x = (player->x + player->sizeWidth / 2) - width / 2;
	y = (player->y + player->sizeHeight / 2) - height / 2;
}

bool PlayerRadious::isContact(Player* player, Key* key, std::vector<Wall>* walls) {
	if (collision(this, key) &&
		!lineIntersectsWall(player->x, player->y, key->getX(), key->getY(), walls))
		return 1;
	return 0;
}

void PlayerRadious::render(SDL_Renderer* renderer, Camera* camera) {
	SDL_Rect rect = {static_cast<int>(x - camera->x),
					 static_cast<int>(y - camera->y), width, height};
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 0, 173, 198, 128);
	SDL_RenderFillRect(renderer, &rect);
}
