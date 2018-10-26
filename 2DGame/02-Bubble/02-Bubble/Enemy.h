#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Enemy{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
	
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	glm::vec2 getPosition();
	void setPlayerPos(glm::vec2 &playerPosAux);
	
private:
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	glm::vec2 playerPos;
};


#endif _ENEMY_INCLUDE


