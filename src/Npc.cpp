#include "include/Npc.h"

#include <SDL2/SDL.h>
#include <SDL_joystick.h>
#include <SDL_keyboard.h>
#include <SDL_scancode.h>
#include <SDL_stdinc.h>

#include <algorithm>
#include <cmath>
#include <codecvt>
#include <ctime>
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <iostream>

#include "include/Collision.h"
#include "include/GameObject.h"
#include "include/Layout1.h"
// Constructor
Npc::Npc(float x, float y, int sizeWidth, int sizeHeight, float speed)
	: GameObject(x, y, sizeWidth, sizeHeight), speed(speed) {}

// Handle keyboard input
void Npc::movement(Clock* clock, Layout1* layout) {
	srand(time(NULL));
	glm::vec2 movement(0.0f, 0.0f);
	int timeOut = 1500;
	/*if (clock->last_tick_time - clock->last_npc_time >= timeOut) {
		headDirection = rand() % 4;
		clock->last_npc_time = clock->last_tick_time;
	}*/
	bool hit = NpcCollision(layout);
	// IF SHI
	if (hit || clock->last_tick_time - clock->last_npc_time >= timeOut) {
		while (1) {
			headDirection = rand() % 4;
			switch (headDirection) {
				case 1:
					x += 1;
					break;
				case 3:
					x -= 1;
					break;
				case 2:
					y += 1;
					break;
				case 0:
					y -= 1;
					break;
			}
			if (!NpcCollision(layout))
				break;
			switch (headDirection) {
				case 1:
					x -= 1.1;
					break;
				case 3:
					x += 1.1;
					break;
				case 2:
					y -= 1.1;
					break;
				case 0:
					y += 1.1;
					break;
			}
		}
        clock->last_npc_time = clock->last_tick_time;
	}

	// MOVEMENT
	switch (headDirection) {
		case 1:
			movement.x += 1.0f;
			break;
		case 3:
			movement.x -= 1.0f;
			break;
		case 2:
			movement.y += 1.0f;
			break;
		case 0:
			movement.y -= 1.0f;
			break;
	}
	movement = glm::normalize(movement);
	movement *= (speed * clock->delta * 0.4f);
	x += movement.x;
	y += movement.y;
}
bool Npc::NpcCollision(Layout1* layout) {
	for (Line line : layout->lines)
		if (collision(this, line)) {
			return true;
		}
	return false;
}
