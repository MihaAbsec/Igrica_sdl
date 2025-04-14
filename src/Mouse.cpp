#include "include/Mouse.h"

#include <iostream>

#include "include/Game.h"

int Mouse::x = 0;
int Mouse::y = 0;
int Mouse::worldX = 0;
int Mouse::worldY = 0;
int Mouse::originalX = 0;
int Mouse::originalY = 0;
int Mouse::dx = 0;
int Mouse::dy = 0;
Uint32 Mouse::buttons = 0;
Uint32 Mouse::lastButtons = 0;

void Mouse::update(SDL_Event& event, Camera* camera) {
	lastButtons = buttons;

	if (event.type == SDL_MOUSEMOTION) {
		// Fizične koordinate miške
		x = event.motion.x;
		y = event.motion.y;

        originalX = x / Game::scale_x;
        originalY = y / Game::scale_y;

		// Preslikaj fizične koordinate na logične koordinate z uporabo Game::scale_x in Game::scale_y
		worldX = originalX + camera->x;
		worldY = originalY + camera->y;

		dx = event.motion.xrel;
		dy = event.motion.yrel;
	}

	if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
		buttons = SDL_GetMouseState(&x, &y);

		// Preslikaj fizične koordinate na logične koordinate z uporabo Game::scale_x in Game::scale_y
		worldX = (x / Game::scale_x) + camera->x;
		worldY = (y / Game::scale_y) + camera->y;
	}

	//std::cout << worldX << " " << worldY << " " << buttons << " " << lastButtons << " " << '\r';
	//std::cout << std::flush;
}

bool Mouse::isButtonDown(Uint8 button) {
	return (buttons & SDL_BUTTON(button)) && !(lastButtons & SDL_BUTTON(button));
}

bool Mouse::isButtonUp(Uint8 button) {
	return !(buttons & SDL_BUTTON(button)) && (lastButtons & SDL_BUTTON(button));
}

bool Mouse::isButtonPressed(Uint8 button) {
	return buttons & SDL_BUTTON(button);
}
