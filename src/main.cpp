#include "include/Game.h"

int main(int argc, char* argv[]) {
	Game* game = new Game(800, 600);
	game->innit();

	if (!game->innit()) {
		return 1;
	}
	while (game->running) {
		game->handleEvents();
		game->update();
		game->render();
		SDL_Delay(16);
	}

	game->cleanup();

	return 0;
}
