#include "include/Saving.h"

#include <fstream>
#include <iostream>

#include "include/Game.h"
Saving::Saving() {
	fileName = "../saves/game_save.bin";
}

void Saving::saveProgress(Game* game, Player* player) {
	std::ofstream data(fileName, std::ios::binary);
	if (!data.is_open()) {
		std::cerr << "Napaka pri ustvarjanju datoteke: " << fileName << std::endl;
		return;
	}
	Progress a;
	a.x = player->getX();
	a.y = player->getY();
	a.keys = game->keysCollected;
	a.kills = player->getKills();
	a.lives = player->getLives();
	a.time = game->timer;
	a.currentLevel = game->currentLevel;
	a.prevKills = game->lvlKills[a.currentLevel - 1];
	a.prevTime = game->lvlTimer[a.currentLevel - 1];
	data.write((char*)&a, sizeof(a));
	data.close();
}

Progress Saving::getProgress() {
	std::ifstream data(fileName, std::ios::binary);
	if (!data.is_open()) {
		std::cerr << "Napaka pri ustvarjanju datoteke: " << fileName << std::endl;
		return {0, 0, 0, 0, 0, 0};
	}
	Progress a;
	data.read((char*)&a, sizeof(a));
	data.close();
	return a;
}

void Saving::emptyFile() {
	std::ofstream file(fileName, std::ios::binary);
	file.close();
}
