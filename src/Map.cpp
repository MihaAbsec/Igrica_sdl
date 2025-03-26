#include "include/Map.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

Map::Map(const std::string& floorTexturePath,
		 const std::string& wallTexturePath,
		 const std::string& mapFilePath,
		 SDL_Renderer* renderer)
	: floorTexture(nullptr), wallTexture(nullptr) {
	// Load textures
	floorTexture = loadTexture(floorTexturePath, renderer);
	wallTexture = loadTexture(wallTexturePath, renderer);

	if (!floorTexture || !wallTexture) {
		std::cerr << "Failed to load one or more textures!" << std::endl;
	}

	// Load map from file
	if (!loadFromFile(mapFilePath)) {
		std::cerr << "Failed to load map from file: " << mapFilePath << std::endl;
		// Create empty map as fallback
		blocks.resize(GRID_SIZE * GRID_SIZE);
		for (int y = 0; y < GRID_SIZE; y++) {
			for (int x = 0; x < GRID_SIZE; x++) {
				Block& block = blocks[y * GRID_SIZE + x];
				block.x = x * BLOCK_SIZE;
				block.y = y * BLOCK_SIZE;
				block.type = FLOOR;
				block.walkable = true;
			}
		}
	}
}

Map::~Map() {
	if (floorTexture) SDL_DestroyTexture(floorTexture);
	if (wallTexture) SDL_DestroyTexture(wallTexture);
}

bool Map::loadFromFile(const std::string& filePath) {
	std::ifstream file(filePath);
	if (!file.is_open()) {
		std::cerr << "Could not open map file: " << filePath << std::endl;
		return false;
	}

	blocks.clear();
	blocks.resize(GRID_SIZE * GRID_SIZE);

	std::string line;
	int y = 0;

	while (std::getline(file, line) && y < GRID_SIZE) {
		for (int x = 0; x < line.length() && x < GRID_SIZE; x++) {
			Block& block = blocks[y * GRID_SIZE + x];
			block.x = x * BLOCK_SIZE;
			block.y = y * BLOCK_SIZE;

			if (line[x] == '0') {
				block.type = FLOOR;
				block.walkable = true;
			} else if (line[x] == '1') {
				block.type = WALL;
				block.walkable = false;
			} else {
				std::cerr << "Invalid block type at (" << x << "," << y << "), defaulting to floor" << std::endl;
				block.type = FLOOR;
				block.walkable = true;
			}
		}
		y++;
	}

	// Fill remaining blocks if file was smaller than our grid
	for (; y < GRID_SIZE; y++) {
		for (int x = 0; x < GRID_SIZE; x++) {
			Block& block = blocks[y * GRID_SIZE + x];
			block.x = x * BLOCK_SIZE;
			block.y = y * BLOCK_SIZE;
			block.type = FLOOR;
			block.walkable = true;
		}
	}

	file.close();
	return true;
}

SDL_Texture* Map::loadTexture(const std::string& filePath, SDL_Renderer* renderer) {
	if (!std::filesystem::exists(filePath)) {
		std::cerr << "Texture file not found: " << filePath << std::endl;
		return nullptr;
	}

	SDL_Surface* surface = IMG_Load(filePath.c_str());
	if (!surface) {
		std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	if (!texture) {
		std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
	}

	return texture;
}

void Map::render(SDL_Renderer* renderer, Camera* camera) {
	if (!renderer || !camera) return;

	for (const auto& block : blocks) {
		SDL_Rect destRect = {
			static_cast<int> (block.x - camera->x),
			static_cast<int> (block.y - camera->y),
			BLOCK_SIZE,
			BLOCK_SIZE};

		SDL_Texture* textureToUse = (block.type == WALL) ? wallTexture : floorTexture;
		if (textureToUse) {
			SDL_RenderCopy(renderer, textureToUse, nullptr, &destRect);
		}
	}
}

bool Map::isWalkable(int x, int y) const {
	if (x < 0 || x >= GRID_SIZE || y < 0 || y >= GRID_SIZE) {
		return false;  // Out of bounds is not walkable
	}
	return blocks[y * GRID_SIZE + x].walkable;
}
