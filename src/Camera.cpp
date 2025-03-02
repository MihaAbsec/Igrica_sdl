#include "include/Camera.h"

#include <iostream>

#include "include/Player.h"

Camera::Camera(float startX, float startY) {
	x = startX;
	y = startY;
}

void Camera::update(Player* player, float worldWidth, float worldHeight, int screenWidth, int screenHeight) {
	x = player->getX() - screenWidth / 2.0f;
	y = player->getY() - screenHeight / 2.0f;
}
