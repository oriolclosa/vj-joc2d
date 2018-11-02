#ifndef _BOSS_INCLUDE
#define _BOSS_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include "Player.h"
#include "Enemy.h"

class Boss: public Enemy {
	
public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, glm::vec2 pos);
	void update(int deltaTime, glm::vec2 *pos_enemies, int n);
	
	void attackPlayer(float damage);
	void takeDamage(float damage);
	float getHealth();	
	int getScore();
	
	void restart();

	int getFase();
	bool getFocus();

	glm::vec2 getCentralPosition();
	glm::vec2 getInnerSize();
	glm::vec2 getCornerPosition();
	glm::vec2 getBottomPosition();
	

private:
	int fase;
	bool focus;

};




#endif _BOSS_INCLUDE