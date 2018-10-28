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


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


#define SCREEN_X 0
#define SCREEN_Y 0


class Scene{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();

	void setCameraMovement(float movement);
	float getCameraMovement();

	void updateLevel(int levelAux);
	void restartLevel();

private:
	void initShaders();

private:
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
	TexturedQuad *tq_character_selection_target_0, *tq_character_selection_target_1, *tq_character_selection_target_2;
	Texture t_wp_main_menu;
	Texture t_title_main_menu;
	Texture t_text_pre_menu;
	Texture t_keys_main_menu;
	Texture t_esc_main_menu;
	Texture t_button_0_main_menu, t_button_1_main_menu, t_button_2_main_menu, t_button_3_main_menu;
	Texture t_wp_game_over, t_wp_game_win;
	Texture t_wp_character_selection, t_character_selection_target;
	Text text;

	Texture texMenuPre;
	TexturedQuad *teqMenuPre;
	Texture texMenuBack;
	TexturedQuad *teqMenuBack;

	float camera_movement;
	
	Level *level;
	int currentLevel;
};

#endif _SCENE_INCLUDE


