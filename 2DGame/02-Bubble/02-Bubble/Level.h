#ifndef _LEVEL_INCLUDE
#define _LEVEL_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "SpriteMap.h"
#include "Player.h"
#include "Enemy.h"
#include "Coin.h"

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

	void updateInfoHealth(float health);
	int getPlayerLifes();

	void setActive(bool activeAux);
	void restart();

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
	Texture backTextures[8];
	Sprite *backSprites[8];
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
	int num_enemies;
	Texture skyTexture;
	Sprite *skySprite;
	Texture texBuildings[5];
	Sprite *sprBuildings[5];

	Texture texInfoHealth;
	Sprite *sprInfoHealth;
	Texture texInfoLifes[3];
	Sprite *sprInfoLifes[3];

	Text text;
	int score;

	Coin *coins[MAX_COINS];
	int num_coins;

	bool active;
};


#endif _LEVEL_INCLUDE

