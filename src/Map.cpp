#include "include/Map.h"

#include <SDL_image.h>

#include <filesystem>
#include <fstream>
#include <iostream>

Map::Map(const std::string& floorTexturePath,
		 const std::string& wallTexturePath,
		 const std::string& mapFilePath,
		 SDL_Renderer* renderer,
		 std::vector<Wall>* walls)
	: renderer(renderer), floorTexture(nullptr), wallTexture(nullptr) {
	//  Naloži teksture
	floorTexture = loadTexture(floorTexturePath);
	wallTexture = loadTexture(wallTexturePath);

	if (!floorTexture) {
		std::cout << "Failed to load floor texture!" << std::endl;
	}
	if (!wallTexture) {
		std::cout << "Failed to load wall texture!" << std::endl;
	}

	//  Naloži mapo
	if (walls) {
		loadFromFile(mapFilePath, walls);
	} else {
		std::cout << "WARNING: walls pointer is null!" << std::endl;
	}
}

Map::~Map() {
	if (floorTexture) SDL_DestroyTexture(floorTexture);
	if (wallTexture) SDL_DestroyTexture(wallTexture);
}

bool Map::loadFromFile(const std::string& mapFilePath, std::vector<Wall>* walls) {
	if (!walls) {
		std::cout << "ERROR: walls pointer is null in loadFromFile!" << std::endl;
		return false;
	}

	std::ifstream file(mapFilePath);
	if (!file.is_open()) {
		std::cout << "ERROR: Could not open map file: " << mapFilePath << std::endl;
		return false;
	}

	walls->clear();
	blocks.clear();
	std::string line;
	int y = 0;

	while (std::getline(file, line)) {
		for (int x = 0; x < line.size(); x++) {
			Block block;
			block.x = x * BLOCK_SIZE;
			block.y = y * BLOCK_SIZE;

			if (line[x] == '1') {  // Stena
				block.type = WALL;
				walls->emplace_back(block.x, block.y, BLOCK_SIZE, BLOCK_SIZE);
			} else {  // Tla
				block.type = FLOOR;
			}

			blocks.push_back(block);
		}
		y++;
	}

	file.close();
	return true;
}

SDL_Texture* Map::loadTexture(const std::string& filePath) {
	if (!std::filesystem::exists(filePath)) {
		std::cout << "Texture file not found: " << filePath << std::endl;
		return nullptr;
	}

	SDL_Surface* surface = IMG_Load(filePath.c_str());
	if (!surface) {
		std::cout << "IMG_Load failed: " << IMG_GetError() << std::endl;
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	if (!texture) {
		std::cout << "SDL_CreateTextureFromSurface failed: " << SDL_GetError() << std::endl;
	}
	return texture;
}

void Map::render(SDL_Renderer* renderer, Camera* camera) {
	if (!renderer || !camera) {
		std::cout << "ERROR: renderer or camera is null in Map::render!" << std::endl;
		return;
	}

	bool useFallback = !floorTexture || !wallTexture;
	if (useFallback) {
		std::cout << "Using fallback colors (textures missing)" << std::endl;
	}

	for (const auto& block : blocks) {
		SDL_Rect destRect = {
			static_cast<int>(block.x - camera->x),
			static_cast<int>(block.y - camera->y),
			BLOCK_SIZE,
			BLOCK_SIZE};

		if (useFallback) {
			SDL_SetRenderDrawColor(renderer,
								   block.type == WALL ? 255 : 0,
								   block.type == WALL ? 0 : 255,
								   0, 255);
			SDL_RenderFillRect(renderer, &destRect);
		} else {
			SDL_Texture* textureToUse = block.type == WALL ? wallTexture : floorTexture;
			if (SDL_RenderCopy(renderer, textureToUse, nullptr, &destRect) != 0) {
				std::cout << "RenderCopy error: " << SDL_GetError() << std::endl;
			}
		}
	}
}
