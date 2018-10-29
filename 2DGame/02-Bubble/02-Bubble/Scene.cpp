#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include <string>
#include <set>
#include <algorithm>
#include <sstream>


Scene::Scene(){
}

Scene::~Scene(){
}

enum scene {
	PRE, MENU, GAME, INSTRUCTIONS, CREDITS, END, CHARACTER
};

void Scene::init() {
	initShaders();

	// Pre_Menu
	glm::vec2 geom[2];
	glm::vec2 texCoords[2];

	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	teqMenuPre = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);

	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	teqMenuBack = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	teqMenuButtons[0] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	teqMenuButtons[1] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	teqMenuButtons[2] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	teqMenuButtons[3] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	teqMenuCharacter = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);

	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(SCREEN_WIDTH * 0.52f, SCREEN_HEIGHT * 0.09851111111f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	teqMenuTitle = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);

	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	tq_wp_main_menu = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);

	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.15f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	tq_title_main_menu = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);

	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.05f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	tq_text_pre_menu = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);

	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(SCREEN_WIDTH * 0.06f, SCREEN_HEIGHT * 0.06f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	tq_keys_main_menu = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);

	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(SCREEN_WIDTH * 0.04f, SCREEN_HEIGHT * 0.06f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	tq_esc_main_menu = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	
	texMenuPre.loadFromFile("images/menu-pre.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texMenuBack.loadFromFile("images/menu-back.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texMenuButtons[0].loadFromFile("images/menu-buttons-play.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texMenuButtons[1].loadFromFile("images/menu-buttons-instructions.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texMenuButtons[2].loadFromFile("images/menu-buttons-credits.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texMenuButtons[3].loadFromFile("images/menu-buttons-exit.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texMenuCharacter.loadFromFile("images/menu-character.png", TEXTURE_PIXEL_FORMAT_RGBA);

	for (int i = 0; i < 3; ++i) {
		texCharacters[i].loadFromFile("images/0/character.png", TEXTURE_PIXEL_FORMAT_RGBA);
		texCharacters[i].setMagFilter(GL_NEAREST);
		sprCharacters[i] = Sprite::createSprite(glm::ivec2(256, 352), glm::vec2(1.0f / 56.0f, 1.0f / 4.0f), &texCharacters[i], &texProgram);
		sprCharacters[i]->setPosition(glm::vec2(20.0f + float(i)*202.5f, 30.0f));
	}

	t_wp_main_menu.loadFromFile("images/wp_main_menu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	t_title_main_menu.loadFromFile("images/title_main_menu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	t_text_pre_menu.loadFromFile("images/text_pre_menu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	t_keys_main_menu.loadFromFile("images/keys_main_menu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	t_keys_main_menu.setMagFilter(GL_NEAREST);
	t_esc_main_menu.loadFromFile("images/esc_main_menu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	t_esc_main_menu.setMagFilter(GL_NEAREST);
	// Select which font you want to use
	if(!text.init("fonts/OpenSans-Regular.ttf"))
		if(!text.init("fonts/OpenSans-Bold.ttf"))
			if(!text.init("fonts/DroidSerif.ttf"))
				cout << "Could not load font!!!" << endl;
	// Main_Menu
	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.15f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	tq_button_0_main_menu = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.15f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	tq_button_1_main_menu = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.15f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	tq_button_2_main_menu = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.15f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	tq_button_3_main_menu = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	t_button_0_main_menu.loadFromFile("images/menu-button.png", TEXTURE_PIXEL_FORMAT_RGBA);
	t_button_0_main_menu.setMagFilter(GL_NEAREST);
	texs[3].loadFromFile("images/menu_1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texs[3].setMagFilter(GL_NEAREST);

	// Game_Over
	t_wp_game_over.loadFromFile("images/wp_game_over.png", TEXTURE_PIXEL_FORMAT_RGBA);
	t_wp_game_over.setMagFilter(GL_NEAREST);
	t_wp_game_win.loadFromFile("images/wp_game_win.png", TEXTURE_PIXEL_FORMAT_RGBA);
	t_wp_game_win.setMagFilter(GL_NEAREST);

	// Character_Selection
	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.9f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	tq_character_selection_target_0 = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);

	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(SCREEN_WIDTH * 0.35f, SCREEN_HEIGHT);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	tq_character_selection_target_1 = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);

	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.85f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	tq_character_selection_target_2 = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);

	t_wp_character_selection.loadFromFile("images/wp_character_selection.png", TEXTURE_PIXEL_FORMAT_RGBA);
	t_wp_character_selection.setMagFilter(GL_NEAREST);
	t_character_selection_target.loadFromFile("images/character_selection_target.png", TEXTURE_PIXEL_FORMAT_RGBA);
	t_character_selection_target.setMagFilter(GL_NEAREST);

	camera_movement = 0.0f;
	currentLevel = -1;

	projection = glm::ortho(0.0f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime) {
	currentTime += deltaTime;
	if (currentLevel >= 0) {
		if(level->complete()) {
			updateLevel(-1);
			/*if (level->getLevelNum() < max_level) {
				updateLevel(level->getLevelNum() + 1);
			}
			else {*/
				Game::instance().setEndGameState(true);
				Game::instance().setRenderScene(5);
			//}
		}
		else {
		level->update(deltaTime);
		setCameraMovement(level->getPlayerPos().x - SCREEN_WIDTH / 2);
		}
	}
}

void Scene::render() {
	glm::mat4 modelview;
	// TODO: crear metodes per cada scena
	projection = glm::ortho(0.0f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	switch(Game::instance().getRenderScene()) {
		case PRE:
			// Pre_Menu
			texProgram.use();
			texProgram.setUniformMatrix4f("projection", projection);
			texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

			modelview = glm::mat4(1.0f);
			texProgram.setUniformMatrix4f("modelview", modelview);
			teqMenuPre->render(texMenuPre);
			break;
		case MENU:
			// Main_Menu
			{
			texProgram.use();
			texProgram.setUniformMatrix4f("projection", projection);
			texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

			modelview = glm::mat4(1.0f);
			texProgram.setUniformMatrix4f("modelview", modelview);

			int button = Game::instance().getSelectedMainButton();
			texProgram.use();
			
			if (button == 0) teqMenuButtons[0]->render(texMenuButtons[0]);
			else if (button == 1) teqMenuButtons[1]->render(texMenuButtons[1]);
			else if (button == 2) teqMenuButtons[2]->render(texMenuButtons[2]);
			else teqMenuButtons[3]->render(texMenuButtons[3]);

			break;
			}
		case INSTRUCTIONS:
			// Menu_Intruccions
			texProgram.use();
			texProgram.setUniformMatrix4f("projection", projection);
			texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
			modelview = glm::mat4(1.0f);
			texProgram.setUniformMatrix4f("modelview", modelview);
			tq_wp_main_menu->render(t_wp_main_menu);
			modelview = glm::translate(glm::mat4(1.0f), glm::vec3(SCREEN_WIDTH * 0.5f - (SCREEN_WIDTH * 0.3f) / 2.f, SCREEN_HEIGHT * 0.1f, 0.f));
			texProgram.setUniformMatrix4f("modelview", modelview);
			tq_title_main_menu->render(t_title_main_menu);
			modelview = glm::translate(glm::mat4(1.0f), glm::vec3(SCREEN_WIDTH * 0.95f - (SCREEN_WIDTH * 0.06f) / 2.f, SCREEN_HEIGHT * 0.82f, 0.f));
			texProgram.setUniformMatrix4f("modelview", modelview);
			tq_keys_main_menu->render(t_keys_main_menu);
			modelview = glm::translate(glm::mat4(1.0f), glm::vec3(SCREEN_WIDTH * 0.95f - (SCREEN_WIDTH * 0.04f) / 2.f, SCREEN_HEIGHT * 0.9f, 0.f));
			texProgram.setUniformMatrix4f("modelview", modelview);
			tq_esc_main_menu->render(t_esc_main_menu);
		
			texProgram.use();
			modelview = glm::translate(glm::mat4(1.0f), glm::vec3(SCREEN_WIDTH * 0.5f - (SCREEN_WIDTH * 0.2f) / 2.f, SCREEN_HEIGHT * 0.8f, 0.f));
			texProgram.setUniformMatrix4f("modelview", modelview);
			tq_button_0_main_menu->render(texs[3]);
			break;
		case CREDITS:
			// Menu_Credits
			texProgram.use();
			texProgram.setUniformMatrix4f("projection", projection);
			texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
			modelview = glm::mat4(1.0f);
			texProgram.setUniformMatrix4f("modelview", modelview);
			tq_wp_main_menu->render(t_wp_main_menu);
			modelview = glm::translate(glm::mat4(1.0f), glm::vec3(SCREEN_WIDTH * 0.5f - (SCREEN_WIDTH * 0.3f) / 2.f, SCREEN_HEIGHT * 0.1f, 0.f));
			texProgram.setUniformMatrix4f("modelview", modelview);
			tq_title_main_menu->render(t_title_main_menu);
			modelview = glm::translate(glm::mat4(1.0f), glm::vec3(SCREEN_WIDTH * 0.95f - (SCREEN_WIDTH * 0.06f) / 2.f, SCREEN_HEIGHT * 0.82f, 0.f));
			texProgram.setUniformMatrix4f("modelview", modelview);
			tq_keys_main_menu->render(t_keys_main_menu);
			modelview = glm::translate(glm::mat4(1.0f), glm::vec3(SCREEN_WIDTH * 0.95f - (SCREEN_WIDTH * 0.04f) / 2.f, SCREEN_HEIGHT * 0.9f, 0.f));
			texProgram.setUniformMatrix4f("modelview", modelview);
			tq_esc_main_menu->render(t_esc_main_menu);
		
			texProgram.use();
			modelview = glm::translate(glm::mat4(1.0f), glm::vec3(SCREEN_WIDTH * 0.5f - (SCREEN_WIDTH * 0.2f) / 2.f, SCREEN_HEIGHT * 0.8f, 0.f));
			texProgram.setUniformMatrix4f("modelview", modelview);
			tq_button_0_main_menu->render(texs[3]);
			break;
		case GAME:
			if (currentLevel >= 0) {
				texProgram.use();
				projection = glm::ortho(camera_movement, float(SCREEN_WIDTH - 1 + camera_movement), float(SCREEN_HEIGHT - 1), 0.f);
				texProgram.setUniformMatrix4f("projection", projection);
				texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
				modelview = glm::mat4(1.0f);
				texProgram.setUniformMatrix4f("modelview", modelview);
				texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

				level->render(texProgram);
			}
			break;
		case END:
			// Game_Over or WIN
			texProgram.use();
			texProgram.setUniformMatrix4f("projection", projection);
			texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

			modelview = glm::mat4(1.0f);
			texProgram.setUniformMatrix4f("modelview", modelview);
			if (Game::instance().getEndGameState()) tq_wp_main_menu->render(t_wp_game_win);
			else tq_wp_main_menu->render(t_wp_game_over);

			modelview = glm::translate(glm::mat4(1.0f), glm::vec3(SCREEN_WIDTH * 0.5f - (SCREEN_WIDTH * 0.2f) / 2.f, SCREEN_HEIGHT * 0.30f + SCREEN_HEIGHT * 0.495f, 0.f));
			texProgram.setUniformMatrix4f("modelview", modelview);
			tq_button_1_main_menu->render(texs[3]);

			char str[12];
			sprintf(str, "Score: %d", Game::instance().getScore());
			text.render(str, glm::vec2(SCREEN_WIDTH * 0.4f, SCREEN_HEIGHT * 0.7f), 32, glm::vec4(1, 1, 1, 1));
			break;
		case CHARACTER:
			// Character_Selection
			texProgram.use();
			texProgram.setUniformMatrix4f("projection", projection);
			texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

			modelview = glm::mat4(1.0f);
			texProgram.setUniformMatrix4f("modelview", modelview);
			teqMenuCharacter->render(texMenuCharacter);

			for (int i = 0; i < 3; ++i) {
				sprCharacters[i]->render();
			}

			int character = Game::instance().getSelectedCharacter();
			//cout << "Char: " << character << endl;
			//cout << "Scene: " << Game::instance().getRenderScene() << endl;
			if (character == 0) {
				modelview = glm::translate(glm::mat4(1.0f), glm::vec3(SCREEN_WIDTH * 0.25f - (SCREEN_WIDTH * 0.3f) / 2.f, SCREEN_HEIGHT * (1.f - 0.9f), 0.f));
				texProgram.setUniformMatrix4f("modelview", modelview);
				tq_character_selection_target_0->render(t_character_selection_target);
			}
			else if (character == 1) {
				modelview = glm::translate(glm::mat4(1.0f), glm::vec3(SCREEN_WIDTH * 0.55f - (SCREEN_WIDTH * 0.35f) / 2.f, 0.f, 0.f));
				texProgram.setUniformMatrix4f("modelview", modelview);
				tq_character_selection_target_1->render(t_character_selection_target);
			}
			else if (character == 2) {
				modelview = glm::translate(glm::mat4(1.0f), glm::vec3(SCREEN_WIDTH * 0.8f - (SCREEN_WIDTH * 0.3f) / 2.f, SCREEN_HEIGHT * (1.f - 0.85f), 0.f));
				texProgram.setUniformMatrix4f("modelview", modelview);
				tq_character_selection_target_2->render(t_character_selection_target);
			
			}
			break;
	}
}

void Scene::initShaders() {
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

void Scene::setCameraMovement(float movement) {
	if (movement < 0.0f) {
		movement = 0.0f;
	}
	/*if (movement >= (map->getMapSize().x - SCREEN_WIDTH)) {
	movement = (map->getMapSize().x - SCREEN_WIDTH);
	}*/
	camera_movement = movement;
}

float Scene::getCameraMovement() {
	return camera_movement;
}

void Scene::updateLevel(int levelAux) {
	camera_movement = 0.0f;
	if (levelAux < 0) {
		currentLevel = -1;
		Game::instance().setScore(Game::instance().getScore() + level->getScore());
		level->setActive(false);
		level = NULL;
	}
	else {
		currentLevel = levelAux;
		level = new Level();
		level->init(texProgram);
	}
}

void Scene::restartLevel() {
	level->restart();
}


