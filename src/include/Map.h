#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include <SDL_image.h>

#include <string>
#include <vector>

#include "Camera.h"

enum BlockType {
	FLOOR = 0,
	WALL = 1
};

struct Block {
	int x;
	int y;
	BlockType type;
	bool walkable;
};

class Map {
   public:
	// Constants for our specific world
	static const int WORLD_SIZE = 1920;
	static const int BLOCK_SIZE = 64;
	static const int GRID_SIZE = WORLD_SIZE / BLOCK_SIZE;  // 60x60 grid

	Map(const std::string& floorTexturePath,
		const std::string& wallTexturePath,
		const std::string& mapFilePath,
		SDL_Renderer* renderer);
	~Map();

	bool loadFromFile(const std::string& filePath);
	void render(SDL_Renderer* renderer, Camera* camera);
	bool isWalkable(int x, int y) const;

   private:
	SDL_Texture* floorTexture;
	SDL_Texture* wallTexture;
	std::vector<Block> blocks;

	SDL_Texture* loadTexture(const std::string& filePath, SDL_Renderer* renderer);
};

#endif	// MAP_H
