#include "include/Map.h"

#include <cstdlib>	   
#include <ctime>	   
#include <filesystem>  
#include <iostream>

Map::Map(const std::string& blockTexturePath, int worldWidth, int worldHeight, int blockSize)
	: worldWidth(worldWidth), worldHeight(worldHeight), blockSize(blockSize), blockTexture(nullptr) {
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	createFloor();
}

Map::~Map() {
	if (blockTexture) {
		SDL_DestroyTexture(blockTexture);
	}
}

SDL_Texture* Map::loadTexture(const std::string& filePath, SDL_Renderer* renderer) {
	std::cout << "Current working directory: " << std::filesystem::current_path() << "\n";

	std::cout << "Loading texture from: " << filePath << "\n";

	if (!std::filesystem::exists(filePath)) {
		std::cerr << "Error: File does not exist at path: " << filePath << "\n";
		return nullptr;
	}

	SDL_Surface* surface = IMG_Load(filePath.c_str());
	if (!surface) {
		std::cerr << "Failed to load image: " << IMG_GetError() << "\n";
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	if (!texture) {
		std::cerr << "Failed to create texture: " << SDL_GetError() << "\n";
	}

	return texture;
}

void Map::createFloor() {
	int numBlocksX = worldWidth / blockSize;
	int numBlocksY = worldHeight / blockSize;

	floorBlocks.resize(numBlocksX * numBlocksY);

	for (int y = 0; y < numBlocksY; ++y) {
		for (int x = 0; x < numBlocksX; ++x) {
			Block block;
			block.x = x * blockSize;
			block.y = y * blockSize;
			floorBlocks[y * numBlocksX + x] = block;
		}
	}
}

void Map::render(SDL_Renderer* renderer, Camera* camera) {
	if (!blockTexture) {
		blockTexture = loadTexture("assets/block.png", renderer);
		if (!blockTexture) {
			std::cerr << "Error: Failed to load block texture. Cannot render map.\n";
			return;	
		}
	}

	for (const auto& block : floorBlocks) {
		SDL_Rect destRect = {
			static_cast<int>(block.x - camera->x),  
			static_cast<int>(block.y - camera->y),  
			blockSize,
			blockSize};
		SDL_RenderCopy(renderer, blockTexture, nullptr, &destRect);
	}
}
