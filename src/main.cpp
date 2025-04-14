#include "include/Clock.h"
#include "include/Game.h"

int main(int argc, char* argv[]) {
	Game* game = new Game(1067, 600);
	Clock* clock = new Clock;

	if (!game->init()) {
		return 1;
	}
	while (game->running) {
		clock->tick();
		game->handleEvents(clock);
		game->update(clock);
		game->render();
	}

	game->cleanup();

	return 0;
}
