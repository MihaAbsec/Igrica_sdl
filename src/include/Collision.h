#ifndef COLLISION_H
#define COLLISION_H
#include "Bullet.h"
#include "Player.h"
#include "Line.h"
void collision(Player& obj1, const Line& obj2); 
bool collision(Bullet& obj1, const Line& obj2);

#endif // COLLISION_H

