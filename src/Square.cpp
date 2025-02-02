#include "include/Square.h"
#include <SDL_joystick.h>
#include <SDL_keyboard.h>
#include <SDL_scancode.h>
#include <SDL_stdinc.h>
#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>
using namespace std;
// Constructor
Square::Square(float x, float y, int size, float speed){
    Square::x = x;
    Square::y = y;
    Square::size = size;
    Square::speed = speed;
}

// Handle keyboard input
void Square::handleInput(SDL_Event& event) {
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    float dx = 0, dy = 0;
    if(state[SDL_SCANCODE_W]){  
        dy -= speed;}
    if(state[SDL_SCANCODE_S]){
        dy += speed;}
    if(state[SDL_SCANCODE_D]){
        dx += speed;}
    if(state[SDL_SCANCODE_A]){
        dx -= speed;}
    if(dx != 0 && dy != 0) {
        dx /= sqrt(2);
        dy /= sqrt(2);
    }
    y += dy;
    x += dx;

}

void Square::update(Line line){
    if(y+size > line.getY()){
        if(!(x+size < line.getX() || x > line.getX()+400))
            y = line.getY()-size;
    }
}

// Render the square
void Square::render(SDL_Renderer* renderer) {
    cout << this->x << " " << this->y << endl;
    SDL_Rect rect = { static_cast<int>(x), static_cast<int>(y), size, size };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color
    SDL_RenderFillRect(renderer, &rect);
}
