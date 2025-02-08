#include "include/Collision.h"

#include "include/Line.h"
#include "include/Square.h"

template <class T, class V>
void collision(T& obj1, const V& obj2) {
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
template void collision<Square, Line>(Square&, const Line&);
