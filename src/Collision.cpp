#include "include/Collision.h"

#include <SDL2/SDL.h>
#include <SDL_rect.h>

#include <iostream>

#include "include/Line.h"
#include "include/Player.h"

// PLAYER
void collision(Player& obj1, const Line& obj2) {
	// zgornja plast
	if (obj1.getY() + obj1.getH() > obj2.getY() && !(obj1.getoldY() + obj1.getH() > obj2.getY()))
		if (!(obj1.getX() + obj1.getW() <= obj2.getX() || obj1.getX() >= obj2.getX() + obj2.getW()))
			obj1.giveXY(obj1.getX(), obj2.getY() - obj1.getH());
	// spodnja plast
	if (obj1.getY() < obj2.getY() + obj2.getH() && !(obj1.getoldY() < obj2.getY() + obj2.getH()))
		if (!(obj1.getX() + obj1.getW() <= obj2.getX() || obj1.getX() >= obj2.getX() + obj2.getW()))
			obj1.giveXY(obj1.getX(), obj2.getY() + obj2.getH());
	// leva plast
	if (obj1.getX() + obj1.getW() > obj2.getX() && !(obj1.getoldX() + obj1.getW() > obj2.getX()))
		if (!(obj1.getY() + obj1.getH() <= obj2.getY() || obj1.getY() >= obj2.getY() + obj2.getH()))
			obj1.giveXY(obj2.getX() - obj1.getW(), obj1.getY());
	// desna plast
	if (obj1.getX() < obj2.getX() + obj2.getW() && !(obj1.getoldX() < obj2.getX() + obj2.getW()))
		if (!(obj1.getY() + obj1.getH() <= obj2.getY() || obj1.getY() >= obj2.getY() + obj2.getH()))
			obj1.giveXY(obj2.getX() + obj2.getW(), obj1.getY());
}
// npc-npc
void collision(Npc* obj1, Npc* obj2) {
	// zgornja plast
	if (obj1->getY() + obj1->getH() > obj2->getY() && !(obj1->getoldY() + obj1->getH() > obj2->getY()))
		if (!(obj1->getX() + obj1->getW() <= obj2->getX() || obj1->getX() >= obj2->getX() + obj2->getW()))
			obj1->giveXY(obj1->getX(), obj2->getY() - obj1->getH());
	// spodnja plast
	if (obj1->getY() < obj2->getY() + obj2->getH() && !(obj1->getoldY() < obj2->getY() + obj2->getH()))
		if (!(obj1->getX() + obj1->getW() <= obj2->getX() || obj1->getX() >= obj2->getX() + obj2->getW()))
			obj1->giveXY(obj1->getX(), obj2->getY() + obj2->getH());
	// leva plast
	if (obj1->getX() + obj1->getW() > obj2->getX() && !(obj1->getoldX() + obj1->getW() > obj2->getX()))
		if (!(obj1->getY() + obj1->getH() <= obj2->getY() || obj1->getY() >= obj2->getY() + obj2->getH()))
			obj1->giveXY(obj2->getX() - obj1->getW(), obj1->getY());
	// desna plast
	if (obj1->getX() < obj2->getX() + obj2->getW() && !(obj1->getoldX() < obj2->getX() + obj2->getW()))
		if (!(obj1->getY() + obj1->getH() <= obj2->getY() || obj1->getY() >= obj2->getY() + obj2->getH()))
			obj1->giveXY(obj2->getX() + obj2->getW(), obj1->getY());
}
// NPC
bool collision(Npc* obj1, const Line& obj2) {
	/*	SDL_Rect npcRect = {
			static_cast<int>(obj1->getX()),
			static_cast<int>(obj1->getY()),
			obj1->getW(),
			obj1->getH()};
		SDL_Rect lineRect = {
			static_cast<int>(obj2.getX()),
			static_cast<int>(obj2.getY()),
			obj2.getW(),
			obj2.getH()};
		if (SDL_HasIntersection(&npcRect, &lineRect))
			return true;

		return false;*/
	float keyLeft = obj1->getX() + 10;
	float keyRight = obj1->getX() + obj1->getW() + 10;
	float keyTop = obj1->getY() + 10;
	float keyBottom = obj1->getY() + obj1->getH() + 10;

	float lineLeft = obj2.getX() + 10;
	float lineRight = obj2.getX() + obj2.getW() + 10;
	float lineTop = obj2.getY() + 10;
	float lineBottom = obj2.getY() + obj2.getH() + 10;

	if (keyRight <= lineLeft ||
		keyLeft >= lineRight ||
		keyBottom <= lineTop ||
		keyTop >= lineBottom) {
		return false;
	}

	return true;
}

void moveCollision(Npc* obj1, const Line* obj2) {
	// zgornja plast
	if (obj1->getY() + obj1->getH() > obj2->getY() && !(obj1->getoldY() + obj1->getH() > obj2->getY()))
		if (!(obj1->getX() + obj1->getW() <= obj2->getX() || obj1->getX() >= obj2->getX() + obj2->getW())) {
			obj1->giveXY(obj1->getX(), obj2->getY() - obj1->getH());
			obj1->fov->contact = 0;
		}
	// spodnja plast
	if (obj1->getY() < obj2->getY() + obj2->getH() && !(obj1->getoldY() < obj2->getY() + obj2->getH()))
		if (!(obj1->getX() + obj1->getW() <= obj2->getX() || obj1->getX() >= obj2->getX() + obj2->getW())) {
			obj1->giveXY(obj1->getX(), obj2->getY() + obj2->getH());
			obj1->fov->contact = 0;
		}
	// leva plast
	if (obj1->getX() + obj1->getW() > obj2->getX() && !(obj1->getoldX() + obj1->getW() > obj2->getX()))
		if (!(obj1->getY() + obj1->getH() <= obj2->getY() || obj1->getY() >= obj2->getY() + obj2->getH())) {
			obj1->giveXY(obj2->getX() - obj1->getW(), obj1->getY());
			obj1->fov->contact = 0;
		}
	// desna plast
	if (obj1->getX() < obj2->getX() + obj2->getW() && !(obj1->getoldX() < obj2->getX() + obj2->getW()))
		if (!(obj1->getY() + obj1->getH() <= obj2->getY() || obj1->getY() >= obj2->getY() + obj2->getH())) {
			obj1->giveXY(obj2->getX() + obj2->getW(), obj1->getY());
			obj1->fov->contact = 0;
		}
}
// BULLET
bool collision(Bullet* obj1, const Line* obj2) {
	/*// zgornja plast
	if (obj1.getY() + obj1.getH() > obj2.getY() && !(obj1.getoldY() + obj1.getH() > obj2.getY()))
		if (!(obj1.getX() + obj1.getW() <= obj2.getX() || obj1.getX() >= obj2.getX() + obj2.getW())) {
			// std::cout << "LALA\n";
			return 1;
		}
	// spodnja plast
	if (obj1.getY() < obj2.getY() + obj2.getH() && !(obj1.getoldY() < obj2.getY() + obj2.getH()))
		if (!(obj1.getX() + obj1.getW() <= obj2.getX() || obj1.getX() >= obj2.getX() + obj2.getW())) {
			// std::cout << "LALA\n";
			return 1;
		}
	// leva plast
	if (obj1.getX() + obj1.getW() > obj2.getX() && !(obj1.getoldX() + obj1.getW() > obj2.getX()))
		if (!(obj1.getY() + obj1.getH() <= obj2.getY() || obj1.getY() >= obj2.getY() + obj2.getH())) {
			// std::cout << "LALA\n";
			return 1;
		}
	// desna plast
	if (obj1.getX() < obj2.getX() + obj2.getW() && !(obj1.getoldX() < obj2.getX() + obj2.getW()))
		if (!(obj1.getY() + obj1.getH() <= obj2.getY() || obj1.getY() >= obj2.getY() + obj2.getH())) {
			// std::cout << "LALA\n";
			return 1;
		}
	return 0;*/
	SDL_Rect bulletRect = {
		static_cast<int>(obj1->getX()),
		static_cast<int>(obj1->getY()),
		obj1->getW(),
		obj1->getH()};
	SDL_Rect fovRect = {
		static_cast<int>(obj2->getX()),
		static_cast<int>(obj2->getY()),
		obj2->getW(),
		obj2->getH()};
	if (SDL_HasIntersection(&bulletRect, &fovRect))
		return true;

	return false;
}

// KEY SPAWN
bool collision(const Key* obj1, const Line& obj2) {
	float keyLeft = obj1->getX();
	float keyRight = obj1->getX() + obj1->getW();
	float keyTop = obj1->getY();
	float keyBottom = obj1->getY() + obj1->getH();

	float lineLeft = obj2.getX();
	float lineRight = obj2.getX() + obj2.getW();
	float lineTop = obj2.getY();
	float lineBottom = obj2.getY() + obj2.getH();

	if (keyRight <= lineLeft ||
		keyLeft >= lineRight ||
		keyBottom <= lineTop ||
		keyTop >= lineBottom) {
		return false;
	}

	return true;
}
// KEY-PLAYER
bool collision(Player* obj1, const Key* obj2) {
	// zgornja plast
	if (obj1->getY() + obj1->getH() > obj2->getY() && !(obj1->getoldY() + obj1->getH() > obj2->getY()))
		if (!(obj1->getX() + obj1->getW() <= obj2->getX() || obj1->getX() >= obj2->getX() + obj2->getW()))
			return true;
	// spodnja plast
	if (obj1->getY() < obj2->getY() + obj2->getH() && !(obj1->getoldY() < obj2->getY() + obj2->getH()))
		if (!(obj1->getX() + obj1->getW() <= obj2->getX() || obj1->getX() >= obj2->getX() + obj2->getW()))
			return true;
	// leva plast
	if (obj1->getX() + obj1->getW() > obj2->getX() && !(obj1->getoldX() + obj1->getW() > obj2->getX()))
		if (!(obj1->getY() + obj1->getH() <= obj2->getY() || obj1->getY() >= obj2->getY() + obj2->getH()))
			return true;
	// desna plast
	if (obj1->getX() < obj2->getX() + obj2->getW() && !(obj1->getoldX() < obj2->getX() + obj2->getW()))
		if (!(obj1->getY() + obj1->getH() <= obj2->getY() || obj1->getY() >= obj2->getY() + obj2->getH()))
			return true;
	return false;
}
bool collision(const Player* obj1, const NpcFov* obj2) {
	/*float keyLeft = obj1->getX();
	float keyRight = obj1->getX() + obj1->getW();

	float keyTop = obj1->getY();
	float keyBottom = obj1->getY() + obj1->getH();

	float lineLeft = obj2->getX();
	float lineRight = obj2->getX() + obj2->getW();
	float lineTop = obj2->getY();
	float lineBottom = obj2->getY() + obj2->getH();

	if (keyRight <= lineLeft ||
		keyLeft >= lineRight ||
		keyBottom <= lineTop ||
		keyTop >= lineBottom) {
		return false;
	}

	return true;*/
	SDL_Rect playerRect = {
		static_cast<int>(obj1->getX()),
		static_cast<int>(obj1->getY()),
		obj1->getW(),
		obj1->getH()};
	SDL_Rect fovRect = {
		static_cast<int>(obj2->getX()),
		static_cast<int>(obj2->getY()),
		obj2->getW(),
		obj2->getH()};
	if (SDL_HasIntersection(&playerRect, &fovRect))
		return true;

	return false;
}
// ČE JE MED PLAYERJEM IN NPC STENA (line-of-sight)
bool lineIntersectsWall(float x1, float y1, float x2, float y2, Layout1* layout) {
	for (const Line& wall : layout->lines) {
		if (lineIntersectsRectangle(x1, y1, x2, y2, wall)) {
			return true;  // If any wall blocks the line, return true
		}
	}
	return false;
}

bool lineIntersectsRectangle(float x1, float y1, float x2, float y2, const Line& wall) {
	float wx1 = wall.getX();
	float wy1 = wall.getY();
	float wx2 = wx1 + wall.getW();
	float wy2 = wy1 + wall.getH();

	return (checkLineIntersection(x1, y1, x2, y2, wx1, wy1, wx2, wy1) ||  // Top edge
			checkLineIntersection(x1, y1, x2, y2, wx1, wy1, wx1, wy2) ||  // Left edge
			checkLineIntersection(x1, y1, x2, y2, wx2, wy1, wx2, wy2) ||  // Right edge
			checkLineIntersection(x1, y1, x2, y2, wx1, wy2, wx2, wy2));	  // Bottom edge
}

bool checkLineIntersection(float x1, float y1, float x2, float y2,
						   float x3, float y3, float x4, float y4) {
	float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	if (den == 0) return false;	 // Parallel lines

	float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
	float u = ((x1 - x3) * (y1 - y2) - (y1 - y3) * (x1 - x2)) / den;

	return (t >= 0 && t <= 1 && u >= 0 && u <= 1);
}

bool collision(Bullet* obj1, const Npc* obj2) {
	SDL_Rect playerRect = {
		static_cast<int>(obj1->getX()),
		static_cast<int>(obj1->getY()),
		obj1->getW(),
		obj1->getH()};
	SDL_Rect fovRect = {
		static_cast<int>(obj2->getX()),
		static_cast<int>(obj2->getY()),
		obj2->getW(),
		obj2->getH()};
	if (SDL_HasIntersection(&playerRect, &fovRect))
		return true;

	return false;
}
