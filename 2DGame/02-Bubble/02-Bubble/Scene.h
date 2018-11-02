#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


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
#include "Level.h"
#include "Texture.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


#define SCREEN_X 0
#define SCREEN_Y 0


class Scene{

public:
	Scene();
	~Scene();

	void preInit();
	void init();
	void update(int deltaTime);
	void render();

	void setCameraMovement(float movement);
	float getCameraMovement();

	void updateLevel(int levelAux);
	void restartLevel();

	void setPlayerPos(glm::vec2 positionAux);

	bool getLoading();

private:
	void initShaders();

private:
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;	
	Texture texs[6];
	TexturedQuad *texQuad[6];
	TexturedQuad *tq_wp_main_menu;
	TexturedQuad *tq_button_1_main_menu;
	Texture t_wp_game_over, t_wp_game_win;
	Text text;

	Texture texMenuPre;
	TexturedQuad *teqMenuPre;
	Texture texMenuBack;
	TexturedQuad *teqMenuBack;
	Texture texMenuButtons[4];
	Texture texMenuButtonsSelected[4];
	TexturedQuad *teqMenuButtons[4];
	Texture texMenuTitle;
	TexturedQuad *teqMenuTitle;
	Texture texMenuCharacter[3];
	TexturedQuad *teqMenuCharacter;
	Texture texMenuCredits;
	Texture texMenuInstructions;
	Texture texMenuScore[2];
	Texture texMenuLoading[5];

	float camera_movement;
	
	Level *level;
	int currentLevel;

	Texture texCharacters[3];
	Sprite *sprCharacters[3];

	bool loading;
};

#endif _SCENE_INCLUDE


