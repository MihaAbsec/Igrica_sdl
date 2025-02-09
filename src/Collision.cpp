#include "include/Collision.h"

#include <iostream>

#include "include/Line.h"
#include "include/Square.h"

void collision(Square& obj1, const Line& obj2) {
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
bool collision(Bullet& obj1, const Line& obj2) {
	// zgornja plast
	if (obj1.getY() + obj1.getH() > obj2.getY() && !(obj1.getoldY() + obj1.getH() > obj2.getY()))
		if (!(obj1.getX() + obj1.getW() <= obj2.getX() || obj1.getX() >= obj2.getX() + obj2.getW())) {
			//std::cout << "LALA\n";
			return 1;
		}
	// spodnja plast
	if (obj1.getY() < obj2.getY() + obj2.getH() && !(obj1.getoldY() < obj2.getY() + obj2.getH()))
		if (!(obj1.getX() + obj1.getW() <= obj2.getX() || obj1.getX() >= obj2.getX() + obj2.getW())) {
			//std::cout << "LALA\n";
			return 1;
		}
	// leva plast
	if (obj1.getX() + obj1.getW() > obj2.getX() && !(obj1.getoldX() + obj1.getW() > obj2.getX()))
		if (!(obj1.getY() + obj1.getH() <= obj2.getY() || obj1.getY() >= obj2.getY() + obj2.getH())) {
			//std::cout << "LALA\n";
			return 1;
		}
	// desna plast
	if (obj1.getX() < obj2.getX() + obj2.getW() && !(obj1.getoldX() < obj2.getX() + obj2.getW()))
		if (!(obj1.getY() + obj1.getH() <= obj2.getY() || obj1.getY() >= obj2.getY() + obj2.getH())) {
			//std::cout << "LALA\n";
			return 1;
		}
	return 0;
}
