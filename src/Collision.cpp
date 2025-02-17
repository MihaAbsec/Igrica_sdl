#include "include/Collision.h"

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
// NPC
bool collision(Npc* obj1, const Line& obj2) {
	const int padding = 10;	 // Expand collision area by 10 pixels

	// Adjusted boundaries for obj1 (with padding)
	float obj1Left = obj1->getX() - padding;
	float obj1Right = obj1->getX() + obj1->getW() + padding;
	float obj1Top = obj1->getY() - padding;
	float obj1Bottom = obj1->getY() + obj1->getH() + padding;

	// Boundaries for obj2 (no padding)
	float obj2Left = obj2.getX();
	float obj2Right = obj2.getX() + obj2.getW();
	float obj2Top = obj2.getY();
	float obj2Bottom = obj2.getY() + obj2.getH();

	// Check for collision
	if (obj1Right > obj2Left && obj1Left < obj2Right &&	 // Horizontal overlap
		obj1Bottom > obj2Top && obj1Top < obj2Bottom) {	 // Vertical overlap
		return true;
	}

	return false;
}
// BULLET
bool collision(Bullet& obj1, const Line& obj2) {
	// zgornja plast
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
	return 0;
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
//KEY-PLAYER
bool collision(Player& obj1, const Key* obj2) {
	// zgornja plast
	if (obj1.getY() + obj1.getH() > obj2->getY() && !(obj1.getoldY() + obj1.getH() > obj2->getY()))
		if (!(obj1.getX() + obj1.getW() <= obj2->getX() || obj1.getX() >= obj2->getX() + obj2->getW()))
            return true;
	// spodnja plast
	if (obj1.getY() < obj2->getY() + obj2->getH() && !(obj1.getoldY() < obj2->getY() + obj2->getH()))
		if (!(obj1.getX() + obj1.getW() <= obj2->getX() || obj1.getX() >= obj2->getX() + obj2->getW()))
            return true;
	// leva plast
	if (obj1.getX() + obj1.getW() > obj2->getX() && !(obj1.getoldX() + obj1.getW() > obj2->getX()))
		if (!(obj1.getY() + obj1.getH() <= obj2->getY() || obj1.getY() >= obj2->getY() + obj2->getH()))
            return true;
	// desna plast
	if (obj1.getX() < obj2->getX() + obj2->getW() && !(obj1.getoldX() < obj2->getX() + obj2->getW()))
		if (!(obj1.getY() + obj1.getH() <= obj2->getY() || obj1.getY() >= obj2->getY() + obj2->getH()))
            return true;
    return false;
}
