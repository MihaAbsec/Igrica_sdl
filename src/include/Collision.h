#ifndef COLLISION_H
#define COLLISION_H
#include "Bullet.h"
#include "Key.h"
#include "Line.h"
#include "Npc.h"
#include "NpcFov.h"
#include "Player.h"
//player-wall
void collision(Player& obj1, const Line& obj2);
//npc-npc
void collision(Npc* obj1, Npc* obj2);
//npc-wall
bool collision(Npc* obj1, const Line& obj2);
void moveCollision(Npc* obj1, const Line* obj2);
//bullet-wall
bool collision(Bullet* obj1, const Line* obj2);
//bullet-npc
bool collision(Bullet* obj1, const Npc* obj2);
//key-wall
bool collision(const Key* obj1, const Line& obj2);
bool collision(Player* obj1, const Key* obj2);
//player-npcfov
bool collision(const Player* obj1, const NpcFov* obj2);
void FovLineCollision(NpcFov* obj1, const Line* obj2);
//NPC DA NE VIDI ČEZ WALL
bool lineIntersectsWall(float, float, float, float, Layout1*);
bool checkLineIntersection(float, float, float, float, float, float, float, float);
bool lineIntersectsRectangle(float, float, float, float, const Line&);
#endif	// COLLISION_H
