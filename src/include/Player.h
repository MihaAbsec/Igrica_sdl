#ifndef SQUARE_H
#define SQUARE_H

#include <SDL2/SDL.h>
#include <SDL_render.h>

#include <vector>

#include "Clock.h"
#include "GameObject.h"
#include "Mouse.h"
#include "PlayerRadious.h"

class Player : public GameObject {
    int lives = 3;
    int kills = 0;
	// GUN
	float gunX, gunY;

	float speed;
	const float prevSpeed = speed;
	bool turn = 0;
	bool move = 0;
	// sprites
	SDL_Texture* agent;
	SDL_Rect idleFrame;
	SDL_Rect deadFrame;
	SDL_Rect shootFrame;
	SDL_Rect celebrateFrame;
	std::vector<SDL_Rect> runFrames;
	std::vector<SDL_Rect> shootFrames;
	int currentFrameRun;	
	int currentFrameShoot;	
	Uint32 lastFrameTime;	

   public:
    friend PlayerRadious;
    PlayerRadious* radious;
	void createSprite();
	void createSprite(SDL_Texture*&, SDL_Renderer*);
	void shooting(bool shot);
	Player(float, float, int, int, float);
	void handleInput(SDL_Event& event, Clock* clock);
	void update(Clock*);
	void render(SDL_Renderer* renderer, Mouse, int, int, Camera*, Game*);
	float getGunX() const {
		return gunX;
	}
	float getGunY() const {
		return gunY;
	}
	void bulletSpawnFix(Mouse);
    void hit(){
        if(lives == 0)
            return;
        lives--;
    };
    int getLives();
    void plusKill(){
        kills++;
    }
    int getKills();
    void die() {
        lives = 0;
    }
    void giveLives(){
        lives = 3;
    }
    void setKills(int n){
        kills = n;
    }
};

#endif	// SQUARE_H
