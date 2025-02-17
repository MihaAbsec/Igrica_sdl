#include "include/Bullet.h"

#include <SDL2/SDL.h>

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

Bullet::Bullet(float x, float y, int width, int height, float speed, int targetX, int targetY)
	: GameObject(x, y, width, height), speed(speed) {
	// Create position and target vectors
	glm::vec2 position(x, y);
	glm::vec2 target(targetX, targetY);

	// Calculate direction vector
	glm::vec2 direction = target - position;

	// Normalize the direction vector
	float length = glm::length(direction);
	if (length != 0) {
		direction = glm::normalize(direction);
	} else {
		direction = glm::vec2(0, 0);  // If length is 0, set direction to zero
	}

	// Store the direction
	dirX = direction.x;
	dirY = direction.y;
}
void Bullet::update(float deltaTime) {
	oldX = x;
	oldY = y;
	x += dirX * speed * deltaTime;
	y += dirY * speed * deltaTime;
}
