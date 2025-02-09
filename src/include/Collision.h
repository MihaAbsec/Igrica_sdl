#ifndef COLLISION_H
#define COLLISION_H
#include "Bullet.h"
#include "Square.h"
#include "Line.h"
void collision(Square& obj1, const Line& obj2); 
bool collision(Bullet& obj1, const Line& obj2);

#endif // COLLISION_H

