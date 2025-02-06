#include "include/Game.h"

int main(int argc, char *argv[]) {
	Game game(800, 600);
	game.innit();

	if (!game.innit()) {
		return 1;  // Initialization failed
	}
	while (game.running) {
		game.handleEvents();
		game.update();
		game.render();
		SDL_Delay(16);	// Cap the frame rate (~60 FPS)
	}

	game.cleanup();

	return 0;
}
