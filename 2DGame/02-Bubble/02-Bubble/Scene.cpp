#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include <string>
#include <set>
#include <algorithm>
#include <sstream>
#include <GL/glut.h>

#define NUM_LEVELS 2

Scene::Scene(){
}

Scene::~Scene(){
}

enum scene {
	PRE, MENU, GAME, INSTRUCTIONS, CREDITS, END, CHARACTER, LOADING
};

void Scene::preInit() {
	initShaders();

	// Loding
	glm::vec2 geom[2];
	glm::vec2 texCoords[2];

	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);

	teqMenuBack = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);

	for (int i = 0; i < 5; ++i) {
		texMenuLoading[i].loadFromFile("images/menu-loading.png", TEXTURE_PIXEL_FORMAT_RGBA);
	}
	
	// Pre_Menu
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	glm::mat4 modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	teqMenuBack->render(texMenuLoading[0]);
}

void Scene::init() {

	// Pre_Menu
	glm::vec2 geom[2];
	glm::vec2 texCoords[2];

	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	teqMenuPre = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
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
	
	texMenuPre.loadFromFile("images/menu-pre.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texMenuBack.loadFromFile("images/menu-back.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texMenuButtons[0].loadFromFile("images/menu-buttons-play.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texMenuButtons[1].loadFromFile("images/menu-buttons-instructions.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texMenuButtons[2].loadFromFile("images/menu-buttons-credits.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texMenuButtons[3].loadFromFile("images/menu-buttons-exit.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texMenuCharacter[0].loadFromFile("images/menu-character-0.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texMenuCharacter[1].loadFromFile("images/menu-character-1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texMenuCharacter[2].loadFromFile("images/menu-character-2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texMenuCredits.loadFromFile("images/menu-credits.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texMenuInstructions.loadFromFile("images/menu-instructions.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texMenuScore[0].loadFromFile("images/menu-score-lost.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texMenuScore[1].loadFromFile("images/menu-score-won.png", TEXTURE_PIXEL_FORMAT_RGBA);

	for (int i = 0; i < 3; ++i) {
		ostringstream path;
		path << "images/" << i << "/characterNo.png";
		texCharacters[i].loadFromFile(path.str(), TEXTURE_PIXEL_FORMAT_RGBA);
		texCharacters[i].setMagFilter(GL_NEAREST);
		sprCharacters[i] = Sprite::createSprite(glm::ivec2(256, 352), glm::vec2(1.0f / 56.0f, 1.0f / 4.0f), &texCharacters[i], &texProgram);
		sprCharacters[i]->setPosition(glm::vec2(18.0f + float(i)*202.5f, 30.0f));
	}

	// Select which font you want to use
	if(!text.init("fonts/ScienceFair.ttf"))
		if(!text.init("fonts/OpenSans.ttf"))
			if(!text.init("fonts/DroidSerif.ttf"))
				//cout << "Could not load font!" << endl;
	// Main_Menu
	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.15f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	tq_button_1_main_menu = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	texs[3].loadFromFile("images/menu_1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texs[3].setMagFilter(GL_NEAREST);

	// Game_Over
	t_wp_game_over.loadFromFile("images/wp_game_over.png", TEXTURE_PIXEL_FORMAT_RGBA);
	t_wp_game_over.setMagFilter(GL_NEAREST);
	t_wp_game_win.loadFromFile("images/wp_game_win.png", TEXTURE_PIXEL_FORMAT_RGBA);
	t_wp_game_win.setMagFilter(GL_NEAREST);

	// Character_Selection

	camera_movement = 0.0f;
	currentLevel = -1;

	projection = glm::ortho(0.0f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime) {
	currentTime += deltaTime;
	if (currentLevel >= 0) {
		if(level->complete()) {
			Game::instance().setScore(Game::instance().getScore() - (3 - level->getPlayerLifes()) * 500);
			int lvl = Game::instance().getCurrentLevel();
			updateLevel(-1);
			if (lvl + 1 < NUM_LEVELS) {
				// updateLevel(-1); Que pasa amb el lvl actual? Gestio mem?
				//cout << lvl << endl;
				Game::instance().setCurrentLevel(lvl + 1);
				updateLevel(lvl + 1);
			}
			else {
				Game::instance().setEndGameState(true);
				Game::instance().setRenderScene(5);
			}
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
			teqMenuBack->render(texMenuInstructions);
			break;
		case CREDITS:
			// Menu_Credits
			texProgram.use();
			texProgram.setUniformMatrix4f("projection", projection);
			texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

			modelview = glm::mat4(1.0f);

			texProgram.setUniformMatrix4f("modelview", modelview);
			teqMenuBack->render(texMenuCredits);
			break;
		case GAME:
			if (currentLevel >= 0) {
				if(getLoading()){
					texProgram.use();
					texProgram.setUniformMatrix4f("projection", projection);
					texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

					glm::mat4 modelview = glm::mat4(1.0f);
					texProgram.setUniformMatrix4f("modelview", modelview);
					teqMenuBack->render(texMenuLoading[0]);
				}
				else {
					texProgram.use();
					projection = glm::ortho(camera_movement, float(SCREEN_WIDTH - 1 + camera_movement), float(SCREEN_HEIGHT - 1), 0.f);
					texProgram.setUniformMatrix4f("projection", projection);
					texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
					modelview = glm::mat4(1.0f);
					texProgram.setUniformMatrix4f("modelview", modelview);
					texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

					level->render(texProgram);
				}
			}
			break;
		case END: {
			// Game_Over or WIN
			texProgram.use();
			texProgram.setUniformMatrix4f("projection", projection);
			texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

			modelview = glm::mat4(1.0f);

			texProgram.setUniformMatrix4f("modelview", modelview);
			teqMenuBack->render(texMenuScore[Game::instance().getEndGameState()]);

			ostringstream textScore;
			textScore << "Score: " << Game::instance().getScore();

			text.render(textScore.str(), glm::vec2(glutGet(GLUT_WINDOW_WIDTH) * 0.5f + 2.0f - ((float(glutGet(GLUT_WINDOW_WIDTH)) / 25.f)*textScore.str().length() / 4.65f), glutGet(GLUT_WINDOW_HEIGHT) * 0.55f + 2.0f), float(glutGet(GLUT_WINDOW_WIDTH)) / 25.f, glm::vec4(0.14453125, 0.15625, 0.15234375, 1));
			text.render(textScore.str(), glm::vec2(glutGet(GLUT_WINDOW_WIDTH) * 0.5f - ((float(glutGet(GLUT_WINDOW_WIDTH)) / 25.f)*textScore.str().length() / 4.65f), glutGet(GLUT_WINDOW_HEIGHT) * 0.55f), float(glutGet(GLUT_WINDOW_WIDTH)) / 25.f, glm::vec4(0.91015625, 0.65625, 0.375, 1));
			break; }
		case CHARACTER:
			// Character_Selection
			texProgram.use();
			texProgram.setUniformMatrix4f("projection", projection);
			texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

			modelview = glm::mat4(1.0f);
			texProgram.setUniformMatrix4f("modelview", modelview);
			int character = Game::instance().getSelectedCharacter();
			teqMenuCharacter->render(texMenuCharacter[character]);

			for (int i = 0; i < 3; ++i) {
				sprCharacters[i]->render();
			}
			break;
	}
}

void Scene::initShaders() {
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		//cout << "Vertex Shader Error" << endl;
		//cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		//cout << "Fragment Shader Error" << endl;
		//cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		//cout << "Shader Linking Error" << endl;
		//cout << "" << texProgram.log() << endl << endl;
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
		level->init(texProgram, currentLevel+1);
	}
}

void Scene::restartLevel() {
	level->restart();
}

void Scene::setPlayerPos(glm::vec2 positionAux) {
	level->setPlayerPos(positionAux);
}

bool Scene::getLoading() {
	if (level == NULL) return true;
	return level->getLoading();
}