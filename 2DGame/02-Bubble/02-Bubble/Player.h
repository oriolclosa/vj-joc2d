#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
	
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	glm::vec2 getPosition();
	void takeDamage(float damage);
	void doDamage(float damage);
	void death();
	float getHealth();
	int getLifes();
	float getDamageDone();
	bool getDirection();

	glm::vec2 getCentralPosition();
	glm::vec2 getBottomPosition();
	glm::vec2 getCornerPosition();

	glm::vec2 getInnerSize();
	
private:
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	int lifes;
	float health;
	bool right;
	int coolDownA1, coolDownA2, coolDownA3;
	float damageDone;
	int coolDownRec1, coolDownRec2;
	int coolDownDamage;
};


#endif _PLAYER_INCLUDE


