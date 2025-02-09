#ifndef MOUSE_H
#define MOUSE_H

#include <SDL2/SDL.h>

class Mouse {
	static int x, y;
	static int dx, dy;
	static Uint32 buttons;
	static Uint32 lastButtons;

   public:
	static void update(SDL_Event &event);

	static bool isButtonDown(Uint8 button);
	static bool isButtonUp(Uint8 button);
	static bool isButtonPressed(Uint8 button);

	static int getX();
	static int getY();
	static int getDX();
	static int getDY();
	static int getButtons() {
		return buttons;
	}
    static int getLastButtons() {
        return lastButtons;
    }
};

#endif
