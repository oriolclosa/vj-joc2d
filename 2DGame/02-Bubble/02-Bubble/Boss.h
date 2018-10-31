#ifndef _BOSS_INCLUDE
#define _BOSS_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include "Player.h"

class Boss {
	
public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, glm::vec2 pos);
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
	int getFase();
	bool getFocus();

private:
	int type;
	int fase;
	float health;
	bool focus;

	glm::ivec2 tileMapDispl, posPlayer, iniPosition;
	glm::vec2 playerPos;
	Texture spritesheet;
	Sprite *sprite;
	Player *player;
	TileMap *map;
};




#endif _BOSS_INCLUDE