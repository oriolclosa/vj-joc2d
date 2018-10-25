#ifndef _SPRITE_DESK_INCLUDE
#define _SPRITE_DESK_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Player.h"
#include <string.h>


class Desk
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setPlayer(Player *p);
	void setPosition(const glm::vec2 &pos);
	void setTarget(const glm::vec2 &pos);

private:
	glm::ivec2 tileMapDispl, posClock;
	Texture spritesheet;
	Sprite *sprite;
	Player *player;
	glm::vec2 target;
};


#endif // _SPRITE_DESK_INCLUDE