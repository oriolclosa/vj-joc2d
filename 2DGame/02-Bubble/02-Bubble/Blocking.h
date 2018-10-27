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

	void restart();

private:
	glm::ivec2 posPlayer, iniPosition;
	Texture spritesheet;
	Sprite *sprite;
};


#endif _BLOCKING_INCLUDE
