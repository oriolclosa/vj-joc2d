#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "SpriteMap.h"
#include "Player.h"
#include "Enemy.h"

#include "Quad.h"
#include "TexturedQuad.h"
#include "Text.h"


#define MAX_ENEMIES 100


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();

	void setCameraMovement(float movement);
	float getCameraMovement();

private:
	void initShaders();

private:
	TileMap *map;
	TileMap *backgroundMap;
	TileMap *spriteMap;
	TileMap *overgroundMap;
	SpriteMap *spritemap;
	Player *player;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;	
	Texture texs[6];
	TexturedQuad *texQuad[6];
	Text text;
	Texture textures[10];
	Sprite *sprites[10];
	Texture backTextures[3];
	Sprite *backSprites[3];
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

	float camera_movement;
};


#endif // _SCENE_INCLUDE

