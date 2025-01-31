#ifndef SQUARE_H
#define SQUARE_H

#include <SDL2/SDL.h>

class Square {
    float x, y;
    int size;
    float speed;
public:
    Square(float, float, int, float); // Constructor
    void handleInput(SDL_Event& event);        // Handle keyboard input
    void update();                             // Update square position
    void render(SDL_Renderer* renderer);       // Render the square
};

#endif // SQUARE_H
