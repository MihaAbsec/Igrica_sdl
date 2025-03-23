//#include "include/GameObject.h"

/*#include "include/Game.h"  // Vključi Game.h za dostop do statičnih spremenljivk

void GameObject::render(SDL_Renderer* renderer, float cameraX, float cameraY) {
	draw_x = x*Game::scale_x;
	draw_y =y* Game::scale_x;
	draw_w =sizeWidth* Game::scale_x;
	draw_h = sizeHeight*Game::scale_y;
	SDL_Rect rect = {
		static_cast<int>((x - cameraX) * Game::scale_x),  // Prilagodi pozicijo X
		static_cast<int>((y - cameraY) * Game::scale_y),  // Prilagodi pozicijo Y
		static_cast<int>(sizeWidth * Game::scale_x),	  // Prilagodi širino
		static_cast<int>(sizeHeight * Game::scale_y)	  // Prilagodi višino
	};
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Bela barva
	SDL_RenderFillRect(renderer, &rect);
}
float GameObject::getX() const {
	//return draw_x;
    return x*Game::scale_x;
}
float GameObject::getY() const {
	//return draw_y;
    return y*Game::scale_y;
}
float GameObject::getoldX() const {
	return oldX;
}
float GameObject::getoldY() const {
	return oldY;
}
int GameObject::getH() const {
//	return draw_h;
    return sizeHeight*Game::scale_y;
}
int GameObject::getW() const {
//	return draw_w;
    return sizeWidth*Game::scale_x;
}*/
