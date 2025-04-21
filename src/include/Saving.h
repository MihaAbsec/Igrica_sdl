#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

#include <iostream>
#include "Player.h"
class Game;
struct Progress {
	float x, y;
    int currentLevel;
	int kills;
	unsigned int time;
	int keys;
	int lives;
    int prevKills;
    int prevTime;
};

class Saving {
   public:
	Saving();
	void saveProgress(Game*, Player*);
    Progress getProgress();
    void emptyFile();
    bool isFileEmpty();

   private:
	std::string fileName;
};
