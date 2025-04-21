#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include <SDL_image.h>

#include <string>
#include <vector>

#include "Camera.h"
#include "Wall.h"

class Map {
   public:
	enum BlockType { FLOOR,
					 WALL };

	static constexpr int BLOCK_SIZE = 64;
	static constexpr int GRID_SIZE = 30;

	struct Block {
		float x, y;
		BlockType type;
	};

	Map(const std::string& floorTexturePath,
		const std::string& wallTexturePath,
		const std::string& mapFilePath,
		SDL_Renderer* renderer,
		std::vector<Wall>* walls);

	~Map();

	Map(const Map&) = delete;
	Map& operator=(const Map&) = delete;

	bool loadFromFile(const std::string& mapFilePath, std::vector<Wall>* walls);
	void render(SDL_Renderer* renderer, Camera* camera);

   private:
	SDL_Texture* floorTexture = nullptr;
	SDL_Texture* wallTexture = nullptr;
	SDL_Renderer* renderer = nullptr;
	std::vector<Block> blocks;

	SDL_Texture* loadTexture(const std::string& filePath);
};

#endif	// MAP_H
