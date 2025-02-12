#ifndef COLLISION_H
#define COLLISION_H
#include "Bullet.h"
#include "Line.h"
#include "Npc.h"
#include "Player.h"
void collision(Player& obj1, const Line& obj2);
bool collision(Npc* obj1, const Line& obj2);
bool collision1(Npc* obj1, const Line& obj2);
bool collision(Bullet& obj1, const Line& obj2);

#endif	// COLLISION_H
