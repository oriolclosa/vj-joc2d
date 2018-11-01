#ifndef _LEVEL_INCLUDE
#define _LEVEL_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "SpriteMap.h"
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"
#include "Coin.h"
#include "Blocking.h"

#include "Quad.h"
#include "TexturedQuad.h"
#include "Text.h"
#include "Scene.h"


#define MAX_ENEMIES 100
#define MAX_COINS 100


class Level{

public:
	Level();
	~Level();

	void init(ShaderProgram &texProgramAux);
	void update(int deltaTime);
	void render(ShaderProgram &texProgramAux);

	glm::vec2 getPlayerPos();
	void setPlayerPos(glm::vec2 positionAux);

	void updateInfoHealth(float health);
	int getPlayerLifes();
	void updatePlayerAttack(float damage);

	void setActive(bool activeAux);
	void restart();
	void updateEnemiesAlive();
	int getScore();

	void setCharacter(int characterAux);
	int getCharacter();
	bool complete();

private:
	TileMap *map;
	TileMap *backgroundMap;
	TileMap *spriteMap;
	TileMap *overgroundMap;
	SpriteMap *spritemap;
	Player *player;
	float currentTime;
	Texture textures[10];
	Sprite *sprites[10];
	Texture backTextures[10];
	Sprite *backSprites[10];
	Texture overTextures[17];
	Sprite *overSprites[17];
	Texture texDesk[6];
	Sprite *sprDesk[6];
	Texture texWall[10];
	Sprite *sprWall[10];
	Texture texObject[10];
	Sprite *sprObject[10];
	Texture walkableTexture;
	Sprite *walkableSprite;
	Enemy *enemies[MAX_ENEMIES];
	Boss *boss;
	int num_enemies;
	Texture skyTexture;
	Sprite *skySprite;
	Texture texBuildings[5];
	Sprite *sprBuildings[5];

	Texture texInfoHealth;
	Sprite *sprInfoHealth;
	Texture texInfoLifes[3];
	Sprite *sprInfoLifes[3];

	Sprite *spr_info_cooldown[4];
	Texture t_info_cooldown[4];

	Text textScore;
	int score;

	Coin *coins[MAX_COINS];
	int num_coins;

	bool active;

	Blocking *blockObject;

	int currentCharacter;
	bool level_complete;
	glm::vec2 pos_anteriors[];
};


#endif _LEVEL_INCLUDE

