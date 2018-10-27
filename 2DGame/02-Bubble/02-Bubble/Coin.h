#ifndef _COIN_INCLUDE
#define _COIN_INCLUDE

#include "Player.h"
#include "Sprite.h"


class Coin {

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, glm::vec2 pos);
	void update(int deltaTime);
	void render();

	void setPlayer(Player *playerAux);
	void setPosition(const glm::vec2 &pos);
	glm::vec2 getPosition();

	void restart();

private:
	glm::ivec2 tileMapDispl, posPlayer, iniPosition;
	Texture spritesheet;
	Sprite *sprite;
	Player *player;
	float extraTime;
};


#endif _COIN_INCLUDE