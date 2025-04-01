#include "include/Camera.h"

#include <iostream>

#include "include/Game.h"
#include "include/Player.h"

Camera::Camera(float startX, float startY) {
	x = startX;
	y = startY;
}

void Camera::update(Player* player, float worldWidth, float worldHeight, int screenWidth, int screenHeight) {
    // Upoštevaj skaliranje pri izračunu pozicije kamere
    x = player->getX() - (screenWidth / 2 );
    y = player->getY() - (screenHeight / 2);
    //std::cout << (int)x << " " << (int)y << '\r';
    //std::cout << std::flush;
}
