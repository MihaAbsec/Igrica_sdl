#ifndef CAMERA_H
#define CAMERA_H
class Game;
class Player;
class Camera {
public:
    float x, y; // Camera position

    Camera(float startX, float startY); 
    void update(Player* player, float worldWidth, float worldHeight, int screenWidth, int screenHeight);
};

#endif

