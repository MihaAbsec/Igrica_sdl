#include "include/Collision.h"

#include <iostream>

#include "include/Game.h"
#include "include/Line.h"
#include "include/Square.h"

template <class T>
void collision(T obj, Line line) {
	// zgornja plast
	if (obj.getY() + obj.getH() > line.getY() && !(obj.getoldY() + obj.getH() > line.getY()))
		if (!(obj.getX() + obj.getW() < line.getX() || obj.getX() > line.getX() + line.getW())) {
			//obj.giveXY(obj.getX(), line.getY() - obj.getH());
			//std::cout << "LALA\n";
            obj.y = line.getY() - obj.getH();
		}
	// spodnja plast
	if (obj.getY() < line.getY() + line.getH() && !(obj.getoldY() < line.getY() + line.getH()))
		if (!(obj.getX() + obj.getW() < line.getX() || obj.getX() > line.getX() + line.getW())) {
			//obj.giveXY(obj.getX(), line.getY() + line.getH());
			//std::cout << "LALA\n";
            obj.y = line.getY() + line.getH();
		}
	// leva plast
	if (obj.getX() + obj.getW() > line.getX() && !(obj.getoldX() + obj.getW() > line.getX()))
		if (!(obj.getY() + obj.getH() < line.getY() || obj.getY() > line.getY() + line.getH())) {
			//obj.giveXY(line.getX() - obj.getW(), obj.getY());
			//std::cout << "LALA\n";
            obj.x = line.getX() - obj.getH();
		}
	// desna plast
	if (obj.getX() < line.getX() + line.getW() && !(obj.getoldX() < line.getX() + line.getW()))
		if (!(obj.getY() + obj.getH() < line.getY() || obj.getY() > line.getY() + line.getH())) {
			//obj.giveXY(line.getX() + line.getW(), obj.getY());
			//std::cout << "LALA\n";
            obj.x = line.getX() + line.getW();
		}
}

template void collision<Square>(Square, Line);

