#ifndef _LEVEL_INCLUDE
#define _LEVEL_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "SpriteMap.h"
#include "Player.h"
#include "Enemy.h"

#include "Quad.h"
#include "TexturedQuad.h"
#include "Text.h"
#include "Scene.h"


#define MAX_ENEMIES 100


class Level{

public:
	Level();
	~Level();

	void init(ShaderProgram &texProgramAux, glm::mat4 &projectionAux);
	void update(int deltaTime);
	void render();

	void setCameraMovement(float movement);
	float getCameraMovement();

	glm::vec2 getPlayerPos();

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
	TexturedQuad *tq_wp_main_menu;
	TexturedQuad *tq_title_main_menu;
	TexturedQuad *tq_text_pre_menu;
	TexturedQuad *tq_keys_main_menu;
	TexturedQuad *tq_esc_main_menu;
	TexturedQuad *tq_button_0_main_menu, *tq_button_1_main_menu, *tq_button_2_main_menu, *tq_button_3_main_menu;
	Texture t_wp_main_menu;
	Texture t_title_main_menu;
	Texture t_text_pre_menu;
	Texture t_keys_main_menu;
	Texture t_esc_main_menu;
	Texture t_button_0_main_menu, t_button_1_main_menu, t_button_2_main_menu, t_button_3_main_menu;
	Text text;
	Texture textures[10];
	Sprite *sprites[10];
	Texture backTextures[6];
	Sprite *backSprites[6];
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
};


#endif _LEVEL_INCLUDE

