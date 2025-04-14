#ifndef MOUSE_H
#define MOUSE_H

#include <SDL2/SDL.h>

#include "Camera.h"

class Mouse {
   public:
	static int x, y;
	static int dx, dy;
	static int worldX, worldY;
	static int originalX, originalY;
	static Uint32 buttons;
	static Uint32 lastButtons;

	static void update(SDL_Event &event, Camera *camera);

	static bool isButtonDown(Uint8 button);
	static bool isButtonUp(Uint8 button);
	static bool isButtonPressed(Uint8 button);

	static int getX() {
		return x;
	}
	static int getY() {
		return y;
	}
	static int getDX() {
		return dx;
	}
	static int getDY() {
		return dy;
	}
	static Uint32 getButtons() {
		return buttons;
	}
	static Uint32 getLastButtons() {
		return lastButtons;
	}
	static float getWorldX() {
		return worldX;
	}
	static float getWorldY() {
		return worldY;
	}
};

#endif
