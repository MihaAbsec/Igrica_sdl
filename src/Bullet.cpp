#include "include/Bullet.h"
#include <SDL2/SDL.h>
#include <cmath>

Bullet::Bullet(float x, float y, int width, int height, float speed, int targetX, int targetY)
	: GameObject(x, y, width, height), speed(speed) {
	// Calculate direction vector
	float diffX = targetX - x;
	float diffY = targetY - y;
	float length = sqrt(diffX * diffX + diffY * diffY);	 // Normalize the vector

	if (length != 0) {
		dirX = diffX / length;
		dirY = diffY / length;
	} else {
		dirX = 0;
		dirY = 0;
	}
}
void Bullet::update(float deltaTime) {
	oldX = x;
	oldY = y;
	x += dirX * speed * deltaTime;
	y += dirY * speed * deltaTime;
}
