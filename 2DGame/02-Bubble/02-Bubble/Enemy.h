#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Player.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Enemy{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, glm::vec2 pos, int enemyType);
	void update(int deltaTime);
	void render();
	
	void setTileMap(TileMap *tileMap);
	void setPlayer(Player *playerAux);
	void setPosition(const glm::vec2 &pos);
	glm::vec2 getPosition();
	void setPlayerPos(glm::vec2 &playerPosAux);
	void attackPlayer(float damage);
	void takeDamage(float damage);
	float getHealth();	
	int getScore();

	void restart();
	
private:
	glm::ivec2 tileMapDispl, posPlayer, iniPosition;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite *sprite;
	Player *player;
	TileMap *map;
	glm::vec2 playerPos;
	float health;
	int type;
};


#endif _ENEMY_INCLUDE