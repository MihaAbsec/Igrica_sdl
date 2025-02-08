#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Square.h"
#include "Line.h"
#include "Clock.h"

class Game {
public:
    Game(int, int);  // Constructor
    ~Game(); // Destructor

    bool innit(); // Initialize SDL, window, renderer, etc.
    void run();        // Run the game loop
    void cleanup();    // Clean up resources
    bool running;

    void render();       // Render the game
    void handleEvents(Clock*); // Handle SDL events (e.g., keyboard input)
    void update();       // Update game logic
    
    SDL_Renderer* renderer;
protected:

    SDL_Window* window;

    Square square;
    std::vector<Line> lines;
    
    int SCREEN_WIDTH, SCREEN_HEIGHT;
};

#endif // GAME_H
