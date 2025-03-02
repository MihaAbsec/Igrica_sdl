#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <filesystem>
#include <string>
#include <vector>

#include "Camera.h"

class Map {
   public:
	Map(const std::string& blockTexturePath, int worldWidth, int worldHeight, int blockSize);
	~Map();

	void render(SDL_Renderer* renderer, Camera*);

   private:
	struct Block {
		int x, y;  
	};

	SDL_Texture* blockTexture;

	int worldWidth;
	int worldHeight;
	int blockSize;

	std::vector<Block> floorBlocks;

	SDL_Texture* loadTexture(const std::string& filePath, SDL_Renderer* renderer);

	void createFloor();
};

#endif	// MAP_H
