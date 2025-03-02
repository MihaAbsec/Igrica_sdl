#include "include/Mouse.h"

#include <iostream>

int Mouse::x = 0;
int Mouse::y = 0;
int Mouse::worldX = 0;
int Mouse::worldY = 0;
int Mouse::dx = 0;
int Mouse::dy = 0;
Uint32 Mouse::buttons = 0;
Uint32 Mouse::lastButtons = 0;

void Mouse::update(SDL_Event& event, Camera* camera) {
	lastButtons = buttons;

	if (event.type == SDL_MOUSEMOTION) {
		x = event.motion.x;
		y = event.motion.y;

		worldX = x + camera->x;
		worldY = y + camera->y;

		dx = event.motion.xrel;
		dy = event.motion.yrel;
	}

	if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
		buttons = SDL_GetMouseState(&x, &y);

		worldX = x + camera->x;
		worldY = y + camera->y;
	}
	std::cout << worldX << " " << worldY << " " << buttons << " " << lastButtons << " " << '\r';
	std::cout << std::flush;
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
