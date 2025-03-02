#include "include/Bullet.h"

#include <SDL2/SDL.h>

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

Bullet::Bullet(float x, float y, int width, int height, float speed, int targetX, int targetY)
	: GameObject(x, y, width, height), speed(speed) {
	glm::vec2 position(x, y);
	glm::vec2 target(targetX, targetY);

	glm::vec2 direction = target - position;

	float length = glm::length(direction);
	if (length != 0) {
		direction = glm::normalize(direction);
	} else {
		direction = glm::vec2(0, 0);  // If length is 0, set direction to zero
	}

	dirX = direction.x;
	dirY = direction.y;
}
void Bullet::update(float deltaTime) {
	oldX = x;
	oldY = y;
	x += dirX * speed * deltaTime;
	y += dirY * speed * deltaTime;
}
