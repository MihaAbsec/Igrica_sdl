#include "include/Menu.h"

#include <SDL_rect.h>

#include <iostream>

#include "SDL_render.h"
#include "include/Game.h"

Menu::Menu(TTF_Font* font)
	: font(font) {}

Menu::~Menu() {
	for (auto texture : buttonTextures) {
		SDL_DestroyTexture(texture);
	}
	buttonTextures.clear();
	buttonRects.clear();

	if (backgroundTexture) {
		SDL_DestroyTexture(backgroundTexture);
		backgroundTexture = nullptr;
	}
}

void Menu::addButton(SDL_Renderer* renderer, const std::string& text, SDL_Rect rect) {
	SDL_Color color = {255, 255, 255};
	SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
	if (surface) {
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		if (texture) {
			buttonTextures.push_back(texture);
			buttonRects.push_back(rect);
		}
	}
}

void Menu::pausedRender(SDL_Renderer* renderer, Game* game) {
	// background
	SDL_Rect background = {300, 100, game->original_width - 600, game->original_height - 200};
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
	SDL_RenderFillRect(renderer, &background);
	SDL_Color color = {255, 255, 255};
	std::string text = "Paused";
	SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
	if (surface) {
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_Rect textRect = {
			static_cast<int>(game->original_width / 2 - (surface->w)),
			static_cast<int>(game->original_height / 3 - (surface->h) / 2),
			surface->w * 2,
			surface->h * 2};
		SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
		SDL_DestroyTexture(textTexture);
		SDL_FreeSurface(surface);
	}

	// Počisti stare gumbe
	if (!buttonTextures.empty()) {
		for (auto texture : buttonTextures) {
			SDL_DestroyTexture(texture);
		}
		buttonTextures.clear();
		buttonRects.clear();
	}
	// Gumbi
	if (!interakcija[0])
		addButton(renderer, " Continue ", {static_cast<int>(game->original_width / 2 - 120 / 2), static_cast<int>(game->original_height / 1.8), 120, 26});
	else
		addButton(renderer, "  Continue  ", {static_cast<int>(game->original_width / 2 - 144 / 2), static_cast<int>(game->original_height / 1.8), 144, 26});
	if (!interakcija[1])
		addButton(renderer, " Restart ", {static_cast<int>(game->original_width / 2 - 108 / 2), static_cast<int>(game->original_height / 1.63), 108, 26});
	else
		addButton(renderer, "  Restart  ", {static_cast<int>(game->original_width / 2 - 132 / 2), static_cast<int>(game->original_height / 1.63), 132, 26});
	if (!interakcija[2])
		addButton(renderer, " Save ", {static_cast<int>(game->original_width / 2 - 72 / 2), static_cast<int>(game->original_height / 1.49), 72, 26});
	else
		addButton(renderer, "  Save  ", {static_cast<int>(game->original_width / 2 - 96 / 2), static_cast<int>(game->original_height / 1.49), 96, 26});
	if (!interakcija[3])
		addButton(renderer, " Exit ", {static_cast<int>(game->original_width / 2 - 72 / 2), static_cast<int>(game->original_height / 1.3), 72, 26});
	else
		addButton(renderer, "  Exit  ", {static_cast<int>(game->original_width / 2 - 96 / 2), static_cast<int>(game->original_height / 1.3), 96, 26});
	for (SDL_Rect& bc : buttonRects) {
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		if (!game->fromSaving && bc.y == static_cast<int>(game->original_height / 1.49)) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
		} else
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(renderer, &bc);
	}
	SDL_RenderCopy(renderer, buttonTextures[0], NULL, &buttonRects[0]);
	SDL_RenderCopy(renderer, buttonTextures[1], NULL, &buttonRects[1]);
	SDL_RenderCopy(renderer, buttonTextures[2], NULL, &buttonRects[2]);
	SDL_RenderCopy(renderer, buttonTextures[3], NULL, &buttonRects[3]);
}

void Menu::handleEvent_Paused(SDL_Event& event, Mouse* mouse, Game* game) {
	interakcija = {0, 0, 0, 0};
	if (mouse->getButtons() == 1) {
		for (size_t i = 0; i < buttonRects.size(); ++i) {
			if (mouse->originalX >= buttonRects[i].x && mouse->originalX <= buttonRects[i].x + buttonRects[i].w &&
				mouse->originalY >= buttonRects[i].y && mouse->originalY <= buttonRects[i].y + buttonRects[i].h) {
				if (i == 0) game->gameState = IN_GAME;	// "Continue" gumb
				if (i == 1) {
					game->gameState = IN_GAME;
					game->restart();
				}  // "Restart" gumb
				if (i == 2) {
					if (!game->fromSaving) {
						game->fromSaving = 1;
						game->saveProgressFromMenu();
					} else {
						game->fromSaving = 0;
						game->emptySaving();
					}
				}
				if (i == 3) {
					game->gameState = START_MENU;  // "Exit" gumb
				}
			}
		}
		Mouse::buttons = 0;
	} else {
		for (size_t i = 0; i < buttonRects.size(); ++i) {
			if (mouse->originalX >= buttonRects[i].x && mouse->originalX <= buttonRects[i].x + buttonRects[i].w &&
				mouse->originalY >= buttonRects[i].y && mouse->originalY <= buttonRects[i].y + buttonRects[i].h) {
				interakcija[i] = 1;
			}
		}
	}
}

void Menu::startMenuRender(SDL_Renderer* renderer, Game* game) {
	// background
	if (!backgroundTexture) {
		SDL_Surface* surface = IMG_Load("assets/start_menu_background.jpg");
		if (surface) {
			backgroundTexture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface);
		}
	}
	if (backgroundTexture) {
		SDL_Rect destRect = {0, 0, game->original_width, game->original_height};
		SDL_RenderCopy(renderer, backgroundTexture, NULL, &destRect);
	}
	if (!buttonTextures.empty()) {
		for (auto texture : buttonTextures) {
			SDL_DestroyTexture(texture);
		}
		buttonTextures.clear();
		buttonRects.clear();
	}
	SDL_Rect destRect = {0, 0, game->original_width, game->original_height};
	SDL_RenderCopy(renderer, backgroundTexture, NULL, &destRect);
	// gumbi
	if (!interakcija[0])
		addButton(renderer, " Start ", {static_cast<int>(game->original_width / 4 - 84), static_cast<int>((game->original_height) / 2.5), 84 * 2, 26 * 2});
	else
		addButton(renderer, "  Start  ", {static_cast<int>(game->original_width / 4 - 108), static_cast<int>((game->original_height) / 2.5), 108 * 2, 26 * 2});
	if (!interakcija[1])
		addButton(renderer, " Continue ", {static_cast<int>(game->original_width / 4 - 120), static_cast<int>(game->original_height / 1.9), 120 * 2, 26 * 2});
	else
		addButton(renderer, "  Continue  ", {static_cast<int>(game->original_width / 4 - 144), static_cast<int>(game->original_height / 1.9), 144 * 2, 26 * 2});
	if (!interakcija[2])
		addButton(renderer, " Quit ", {static_cast<int>(game->original_width / 4 - 72), static_cast<int>(game->original_height / 1.5), 72 * 2, 26 * 2});
	else
		addButton(renderer, "  Quit  ", {static_cast<int>(game->original_width / 4 - 96), static_cast<int>(game->original_height / 1.5), 96 * 2, 26 * 2});

	for (SDL_Rect& bc : buttonRects) {
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(renderer, &bc);
	}
	SDL_RenderCopy(renderer, buttonTextures[0], NULL, &buttonRects[0]);
	SDL_RenderCopy(renderer, buttonTextures[1], NULL, &buttonRects[1]);
	SDL_RenderCopy(renderer, buttonTextures[2], NULL, &buttonRects[2]);
}

void Menu::handleEvent_StartMenu(SDL_Event& event, Mouse* mouse, Game* game) {
	interakcija = {0, 0, 0};
	if (mouse->getButtons() == 1) {
		for (size_t i = 0; i < buttonRects.size(); ++i) {
			if (mouse->originalX >= buttonRects[i].x && mouse->originalX <= buttonRects[i].x + buttonRects[i].w &&
				mouse->originalY >= buttonRects[i].y && mouse->originalY <= buttonRects[i].y + buttonRects[i].h) {
				if (i == 0) {
					game->gameState = IN_GAME;
					game->reset();
					Mouse::buttons = 0;
				}  // "Start" gumb
				if (i == 1) {
					if (game->isSavingEmpty())
						return;
					game->gameState = IN_GAME;
					game->setGameFromSaveing();
				}  // "Continue" gumb
				if (i == 2) game->setRunning(0);  // "Quit" gumb
				Mouse::buttons = 0;
			}
		}
	} else
		for (size_t i = 0; i < buttonRects.size(); ++i) {
			if (mouse->originalX >= buttonRects[i].x && mouse->originalX <= buttonRects[i].x + buttonRects[i].w &&
				mouse->originalY >= buttonRects[i].y && mouse->originalY <= buttonRects[i].y + buttonRects[i].h) {
				interakcija[i] = 1;
			}
		}
}

void Menu::gameOverMenu(SDL_Renderer* renderer, Game* game) {
	// background
	SDL_Rect background = {300, 100, game->original_width - 600, game->original_height - 200};
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
	SDL_RenderFillRect(renderer, &background);
	SDL_Color color = {255, 255, 255};
	std::string text = "Game Over";
	SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
	if (surface) {
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_Rect textRect = {
			static_cast<int>(game->original_width / 2 - (surface->w)),
			static_cast<int>(game->original_height / 3 - (surface->h) / 2),
			surface->w * 2,
			surface->h * 2};
		SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
		SDL_DestroyTexture(textTexture);
		SDL_FreeSurface(surface);
	}

	// Počisti stare gumbe
	if (!buttonTextures.empty()) {
		for (auto texture : buttonTextures) {
			SDL_DestroyTexture(texture);
		}
		buttonTextures.clear();
		buttonRects.clear();
	}

	// Gumbi
	if (!interakcija[0])
		addButton(renderer, " Restart ", {static_cast<int>(game->original_width / 2 - 108 / 2), static_cast<int>(game->original_height / 1.6), 108, 26});
	else
		addButton(renderer, "  Restart  ", {static_cast<int>(game->original_width / 2 - 132 / 2), static_cast<int>(game->original_height / 1.6), 132, 26});
	if (!interakcija[1])
		addButton(renderer, " Replay ", {static_cast<int>(game->original_width / 2 - 96 / 2), static_cast<int>(game->original_height / 1.47), 96, 26});
	else
		addButton(renderer, "  Replay  ", {static_cast<int>(game->original_width / 2 - 120 / 2), static_cast<int>(game->original_height / 1.47), 120, 26});
	if (!interakcija[2])
		addButton(renderer, " Exit ", {static_cast<int>(game->original_width / 2 - 72 / 2), static_cast<int>(game->original_height / 1.35), 72, 26});
	else
		addButton(renderer, "  Exit  ", {static_cast<int>(game->original_width / 2 - 96 / 2), static_cast<int>(game->original_height / 1.35), 96, 26});
	for (SDL_Rect& bc : buttonRects) {
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(renderer, &bc);
	}
	SDL_RenderCopy(renderer, buttonTextures[0], NULL, &buttonRects[0]);
	SDL_RenderCopy(renderer, buttonTextures[1], NULL, &buttonRects[1]);
	SDL_RenderCopy(renderer, buttonTextures[2], NULL, &buttonRects[2]);
}
void Menu::handleEvent_GameOver(SDL_Event& event, Mouse* mouse, Game* game) {
	interakcija = {0, 0, 0};
	if (mouse->getButtons() == 1) {
		for (size_t i = 0; i < buttonRects.size(); ++i) {
			if (mouse->originalX >= buttonRects[i].x && mouse->originalX <= buttonRects[i].x + buttonRects[i].w &&
				mouse->originalY >= buttonRects[i].y && mouse->originalY <= buttonRects[i].y + buttonRects[i].h) {
				if (i == 0) {
					// currentState = IN_GAME;
					game->gameState = IN_GAME;
					game->reset();
				}  // "Start" gumb
				if (i == 1) {
					game->prevGameState = game->gameState;
					game->gameState = REPLAY_MODE;
				}
				if (i == 2)	 // game->setRunning(0);  // "Quit" gumb
					game->gameState = START_MENU;
			}
		}
		Mouse::buttons = 0;
	} else
		for (size_t i = 0; i < buttonRects.size(); ++i) {
			if (mouse->originalX >= buttonRects[i].x && mouse->originalX <= buttonRects[i].x + buttonRects[i].w &&
				mouse->originalY >= buttonRects[i].y && mouse->originalY <= buttonRects[i].y + buttonRects[i].h) {
				interakcija[i] = 1;
			}
		}
}
void Menu::levelCompleteMenu(SDL_Renderer* renderer, Game* game) {
	// background
	SDL_Rect background = {300, 100, game->original_width - 600, game->original_height - 200};
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
	SDL_RenderFillRect(renderer, &background);
	SDL_Color color = {255, 255, 255};
	std::string text = "Level Complete";
	SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
	if (surface) {
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_Rect textRect = {
			static_cast<int>(game->original_width / 2 - (surface->w)),
			static_cast<int>(game->original_height / 3 - (surface->h) / 2),
			surface->w * 2,
			surface->h * 2};
		SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
		SDL_DestroyTexture(textTexture);
		SDL_FreeSurface(surface);
	}

	// Počisti stare gumbe
	if (!buttonTextures.empty()) {
		for (auto texture : buttonTextures) {
			SDL_DestroyTexture(texture);
		}
		buttonTextures.clear();
		buttonRects.clear();
	}
	// Gumbi
	if (!interakcija[0])
		addButton(renderer, " Next ", {static_cast<int>(game->original_width / 2 - 72 / 2), static_cast<int>(game->original_height / 1.6), 72, 26});
	else
		addButton(renderer, "  Next  ", {static_cast<int>(game->original_width / 2 - 96 / 2), static_cast<int>(game->original_height / 1.6), 96, 26});
	if (!interakcija[1])
		addButton(renderer, " Replay ", {static_cast<int>(game->original_width / 2 - 96 / 2), static_cast<int>(game->original_height / 1.4), 96, 26});
	else
		addButton(renderer, "  Replay  ", {static_cast<int>(game->original_width / 2 - 120 / 2), static_cast<int>(game->original_height / 1.4), 120, 26});

	for (SDL_Rect& bc : buttonRects) {
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(renderer, &bc);
	}
	SDL_RenderCopy(renderer, buttonTextures[0], NULL, &buttonRects[0]);
	SDL_RenderCopy(renderer, buttonTextures[1], NULL, &buttonRects[1]);
}
void Menu::handleEvent_LevelComplete(SDL_Event& event, Mouse* mouse, Game* game) {
	interakcija = {0, 0};
	if (mouse->getButtons() == 1) {
		for (size_t i = 0; i < buttonRects.size(); ++i) {
			if (mouse->originalX >= buttonRects[i].x && mouse->originalX <= buttonRects[i].x + buttonRects[i].w &&
				mouse->originalY >= buttonRects[i].y && mouse->originalY <= buttonRects[i].y + buttonRects[i].h) {
				if (i == 0) {
					game->gameState = IN_GAME;
					game->restart();
				}  // "Start" gumb
				if (i == 1) {
					game->prevGameState = game->gameState;
					game->gameState = REPLAY_MODE;
				}
				Mouse::buttons = 0;
			}
		}
		Mouse::buttons = 0;
	} else
		for (size_t i = 0; i < buttonRects.size(); ++i) {
			if (mouse->originalX >= buttonRects[i].x && mouse->originalX <= buttonRects[i].x + buttonRects[i].w &&
				mouse->originalY >= buttonRects[i].y && mouse->originalY <= buttonRects[i].y + buttonRects[i].h) {
				interakcija[i] = 1;
			}
		}
}
void Menu::gameWinnerMenu(SDL_Renderer* renderer, Game* game) {
	// background
	SDL_Rect background = {300, 100, game->original_width - 600, game->original_height - 200};
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
	SDL_RenderFillRect(renderer, &background);
	SDL_Color color = {212, 175, 55};
	std::string text = "YOU WON!";
	SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
	if (surface) {
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_Rect textRect = {
			static_cast<int>(game->original_width / 2 - (surface->w)),
			static_cast<int>(game->original_height / 3 - (surface->h) / 2),
			surface->w * 2,
			surface->h * 2};
		SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
		SDL_DestroyTexture(textTexture);
		SDL_FreeSurface(surface);
	}

	// Počisti stare gumbe
	if (!buttonTextures.empty()) {
		for (auto texture : buttonTextures) {
			SDL_DestroyTexture(texture);
		}
		buttonTextures.clear();
		buttonRects.clear();
	}
	// Gumbi
	if (!interakcija[0])
		addButton(renderer, " Restart ", {static_cast<int>(game->original_width / 2 - 108 / 2), static_cast<int>(game->original_height / 1.6), 108, 26});
	else
		addButton(renderer, "  Restart  ", {static_cast<int>(game->original_width / 2 - 132 / 2), static_cast<int>(game->original_height / 1.6), 132, 26});
	if (!interakcija[1])
		addButton(renderer, " Replay ", {static_cast<int>(game->original_width / 2 - 96 / 2), static_cast<int>(game->original_height / 1.47), 96, 26});
	else
		addButton(renderer, "  Replay  ", {static_cast<int>(game->original_width / 2 - 120 / 2), static_cast<int>(game->original_height / 1.47), 120, 26});

	if (!interakcija[2])
		addButton(renderer, " Exit ", {static_cast<int>(game->original_width / 2 - 72 / 2), static_cast<int>(game->original_height / 1.35), 72, 26});
	else
		addButton(renderer, "  Exit  ", {static_cast<int>(game->original_width / 2 - 96 / 2), static_cast<int>(game->original_height / 1.35), 96, 26});

	if (!interakcija[3])
		addButton(renderer, " Replay 1 ", {static_cast<int>(game->original_width / 1.5 - 120 / 2), static_cast<int>(game->original_height / 1.5), 120 / 2, 26 / 2});
	else
		addButton(renderer, "  Replay 1  ", {static_cast<int>(game->original_width / 1.5 - 144 / 2), static_cast<int>(game->original_height / 1.5), 144 / 2, 26 / 2});
	if (!interakcija[4])
		addButton(renderer, " Replay 2 ", {static_cast<int>(game->original_width / 1.5 - 120 / 2), static_cast<int>(game->original_height / 1.45 + 0.3), 120 / 2, 26 / 2});
	else
		addButton(renderer, "  Replay 2  ", {static_cast<int>(game->original_width / 1.5 - 144 / 2), static_cast<int>(game->original_height / 1.45 + 0.3), 144 / 2, 26 / 2});
	if (!interakcija[5])
		addButton(renderer, " Replay 3 ", {static_cast<int>(game->original_width / 1.5 - 120 / 2), static_cast<int>(game->original_height / 1.4), 120 / 2, 26 / 2});
	else
		addButton(renderer, "  Replay 3  ", {static_cast<int>(game->original_width / 1.5 - 144 / 2), static_cast<int>(game->original_height / 1.4), 144 / 2, 26 / 2});
	for (SDL_Rect& bc : buttonRects) {
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		if (!replayButton &&
			(bc.x == static_cast<int>(game->original_width / 1.5 - 120 / 2) ||
			 bc.x == static_cast<int>(game->original_width / 1.5 - 144 / 2)))
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		else
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(renderer, &bc);
	}
	SDL_RenderCopy(renderer, buttonTextures[0], NULL, &buttonRects[0]);
	SDL_RenderCopy(renderer, buttonTextures[1], NULL, &buttonRects[1]);
	SDL_RenderCopy(renderer, buttonTextures[2], NULL, &buttonRects[2]);
	if (replayButton == 1) {
		SDL_RenderCopy(renderer, buttonTextures[3], NULL, &buttonRects[3]);
		SDL_RenderCopy(renderer, buttonTextures[4], NULL, &buttonRects[4]);
		SDL_RenderCopy(renderer, buttonTextures[5], NULL, &buttonRects[5]);
	}
}
void Menu::handleEvent_GameWinner(SDL_Event& event, Mouse* mouse, Game* game) {
	interakcija = {0, 0, 0, 0, 0, 0};
	if (mouse->getButtons() == 1) {
		for (size_t i = 0; i < buttonRects.size(); ++i) {
			if (mouse->originalX >= buttonRects[i].x && mouse->originalX <= buttonRects[i].x + buttonRects[i].w &&
				mouse->originalY >= buttonRects[i].y && mouse->originalY <= buttonRects[i].y + buttonRects[i].h) {
				if (i == 0) {
					replayButton = 0;
					if (game->fromSaving)
						game->emptySaving();
					game->gameState = IN_GAME;
					game->reset();
				}  // "restart" gumb
				if (i == 1) {
					// game->prevGameState = game->gameState;
					//  game->gameState = REPLAY_MODE;
					replayButton = !replayButton;
				}
				if (i == 2) {
					replayButton = 0;
					game->gameState = START_MENU;
					if (game->fromSaving)
						game->emptySaving();
				}  // game->setRunning(0);  // "Exit" gumb
				if (i == 3 && replayButton) {
					game->resetReplayPosition();
					game->loadLevel(1, false);
					game->currentLevel = 2;
					game->prevGameState = game->gameState;
					game->gameState = REPLAY_MODE;
					replayButton = 0;
				}
				if (i == 4 && replayButton) {
					game->resetReplayPosition();
					game->loadLevel(2, false);
					game->currentLevel = 3;
					game->prevGameState = game->gameState;
					game->gameState = REPLAY_MODE;
					replayButton = 0;
				}
				if (i == 5 && replayButton) {
					game->resetReplayPosition();
					game->loadLevel(3, false);
					game->currentLevel = 4;
					game->prevGameState = game->gameState;
					game->gameState = REPLAY_MODE;
					replayButton = 0;
				}
			}
		}
		Mouse::buttons = 0;
	} else
		for (size_t i = 0; i < buttonRects.size(); ++i) {
			if (mouse->originalX >= buttonRects[i].x && mouse->originalX <= buttonRects[i].x + buttonRects[i].w &&
				mouse->originalY >= buttonRects[i].y && mouse->originalY <= buttonRects[i].y + buttonRects[i].h) {
				interakcija[i] = 1;
			}
		}
}
