#ifndef _BLOCKING_INCLUDE
#define _BLOCKING_INCLUDE


#include "Sprite.h"


class Blocking {

public:
	void init(ShaderProgram &shaderProgram, glm::vec2 pos);
	void update(int deltaTime);
	void render();

	void setPosition(const glm::vec2 &pos);
	glm::vec2 getPosition();
	void setPlayerPos(glm::vec2 &playerPosAux);

	void restart();

private:
	glm::ivec2 posPlayer, iniPosition, playerPos;
	Texture spritesheet;
	Sprite *sprite;

	int status;
	float moved;
};


#endif _BLOCKING_INCLUDE
