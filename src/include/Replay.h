#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

#include <fstream>
#include "Clock.h"
class Game;
struct Coordinates {
	float x, y;
};

class Replay {
   public:
	Replay() {}
	Replay(int);
	void recordPositions(float, float, unsigned int);
	Coordinates getPositions(Clock*, Game*);
	void removeFile();
	void emptyFile(int);
	void setLvl(int);

   private:
	std::string fileName;
	unsigned int delayTime = 0;
    unsigned int replayTime = 0;
    unsigned int dataPosition = 0;
    int frames = 10;
};
