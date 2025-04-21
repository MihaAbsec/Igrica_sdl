#include "include/Replay.h"

#include <SDL2/SDL.h>

#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <memory>
#include <string>

#include "include/Game.h"
Replay::Replay(int lvl) {
	fileName = "../saves/level" + std::to_string(lvl) + "_replay.bin";
	// Preveri, ali je datoteka ustvarjena
	std::ofstream testFile(fileName, std::ios::binary | std::ios::app);
	if (!testFile.is_open()) {
		std::cerr << "Napaka pri ustvarjanju datoteke: " << fileName << std::endl;
	} else
		testFile.close();
}

void Replay::setLvl(int lvl) {
	fileName = "../saves/level" + std::to_string(lvl) + "_replay.bin";
}

void Replay::recordPositions(float x, float y, unsigned int time) {
	std::ofstream data(fileName, std::ios::binary | std::ios::app);
	if (!data.is_open()) {
		std::cerr << "Napaka pri odpiranju datoteke: " << fileName << std::endl;
		return;
	}
	if (time - delayTime >= frames) {
		Coordinates a;
		a.x = x;
		a.y = y;
		data.write(reinterpret_cast<const char*>(&a), sizeof(a));
		delayTime = time;
	}
	data.close();
}

Coordinates Replay::getPositions(Clock* clock, Game* game) {
	std::ifstream data(fileName, std::ios::binary);
	if (!data.is_open()) {
		std::cerr << "Napaka pri odpiranju datoteke: " << fileName << std::endl;
		return {192, 192};
	}
	Coordinates a;
	data.seekg(0, std::ios::end);
	if (data.tellg() / sizeof(a) == dataPosition) {
		/*if (game->prevGameState == LEVEL_COMPLETE)
			game->gameState = LEVEL_COMPLETE;
		else
			game->gameState = GAME_WINNER;*/
        game->gameState = game->prevGameState;
		dataPosition = 0;
        data.close();
		return {192, 192};
	}
	if (clock->last_tick_time - replayTime >= frames) {
		replayTime = clock->last_tick_time;
		dataPosition++;
		data.clear();
		data.seekg(dataPosition * sizeof(a), std::ios::beg);
		data.read((char*)&a, sizeof(a));
        data.close();
		return a;
	}
	data.clear();
	data.seekg(dataPosition * sizeof(a), std::ios::beg);
	data.read((char*)&a, sizeof(a));
    data.close();
	return a;
}

void Replay::emptyFile(int lvl) {
	fileName = "../saves/level" + std::to_string(lvl) + "_replay.bin";
	std::ofstream file(fileName, std::ios::binary);
	file.close();
	std::filesystem::resize_file(fileName, 0);
}

void Replay::removeFile() {
	std::remove(reinterpret_cast<const char*>(fileName.c_str()));
}
