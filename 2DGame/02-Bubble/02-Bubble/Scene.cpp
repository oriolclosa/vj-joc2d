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


void Scene::init() {
	initShaders();

	// Menu_0
	glm::vec2 geom[2];
	glm::vec2 texCoords[2];

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
	

	t_wp_main_menu.loadFromFile("images/wp_main_menu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	t_wp_main_menu.setMagFilter(GL_NEAREST);
	t_title_main_menu.loadFromFile("images/title_main_menu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	t_title_main_menu.setMagFilter(GL_NEAREST);
	t_text_pre_menu.loadFromFile("images/text_pre_menu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	t_text_pre_menu.setMagFilter(GL_NEAREST);
	t_keys_main_menu.loadFromFile("images/keys_main_menu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	t_keys_main_menu.setMagFilter(GL_NEAREST);
	t_esc_main_menu.loadFromFile("images/esc_main_menu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	t_esc_main_menu.setMagFilter(GL_NEAREST);
	// Select which font you want to use
	if(!text.init("fonts/OpenSans-Regular.ttf"))
		if(!text.init("fonts/OpenSans-Bold.ttf"))
			if(!text.init("fonts/DroidSerif.ttf"))
				cout << "Could not load font!!!" << endl;
	// Menu_1
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
	t_button_0_main_menu.loadFromFile("images/menu_0.png", TEXTURE_PIXEL_FORMAT_RGBA);
	t_button_0_main_menu.setMagFilter(GL_NEAREST);
	texs[3].loadFromFile("images/menu_1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texs[3].setMagFilter(GL_NEAREST);

	camera_movement = 0.0f;
	levels[0] = new Level();
	levels[0]->init(texProgram);
	currentLevel = 0;

	projection = glm::ortho(0.0f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime) {
	currentTime += deltaTime;
	levels[currentLevel]->update(deltaTime);
	setCameraMovement(levels[currentLevel]->getPlayerPos().x - SCREEN_WIDTH / 2);
}

void Scene::render() {
	glm::mat4 modelview;
	// TODO: crear metodes per cada scena
	switch(Game::instance().getRenderScene()) {
		case 0:
			// Pre_Menu
			texProgram.use();
			texProgram.setUniformMatrix4f("projection", projection);
			texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

			modelview = glm::mat4(1.0f);
			texProgram.setUniformMatrix4f("modelview", modelview);
			tq_wp_main_menu->render(t_wp_main_menu);

			modelview = glm::translate(glm::mat4(1.0f), glm::vec3(SCREEN_WIDTH * 0.5f - (SCREEN_WIDTH * 0.3f) / 2.f, SCREEN_HEIGHT * 0.1f, 0.f));
			texProgram.setUniformMatrix4f("modelview", modelview);
			tq_title_main_menu->render(t_title_main_menu);

			modelview = glm::translate(glm::mat4(1.0f), glm::vec3(SCREEN_WIDTH * 0.5f - (SCREEN_WIDTH * 0.3f) / 2.f, SCREEN_HEIGHT * 0.8f, 0.f));
			texProgram.setUniformMatrix4f("modelview", modelview);
			tq_text_pre_menu->render(t_text_pre_menu);

			modelview = glm::translate(glm::mat4(1.0f), glm::vec3(SCREEN_WIDTH * 0.95f - (SCREEN_WIDTH * 0.04f) / 2.f, SCREEN_HEIGHT * 0.9f, 0.f));
			texProgram.setUniformMatrix4f("modelview", modelview);
			tq_esc_main_menu->render(t_esc_main_menu);
			//text.render("Untitled 2D Game", glm::vec2(SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.225f), 64, glm::vec4(1, 1, 1, 1));
			//text.render("Press F to start the game", glm::vec2(SCREEN_WIDTH * 0.375f, SCREEN_HEIGHT * 0.85f), 24, glm::vec4(1, 1, 1, 1));
			break;
		case 1:
			// Main_Menu
			{
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
			//text.render("Untitled 2D Game", glm::vec2(SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.225f), 64, glm::vec4(1, 1, 1, 1));

			int button = Game::instance().getSelectedMainButton();
			cout << button << endl;
			texProgram.use();
			modelview = glm::translate(glm::mat4(1.0f), glm::vec3(SCREEN_WIDTH * 0.5f - (SCREEN_WIDTH * 0.2f) / 2.f, SCREEN_HEIGHT * 0.30f, 0.f));
			texProgram.setUniformMatrix4f("modelview", modelview);
			if (button == 0) tq_button_0_main_menu->render(texs[3]);
			else tq_button_0_main_menu->render(t_button_0_main_menu);
			modelview = glm::translate(glm::mat4(1.0f), glm::vec3(SCREEN_WIDTH * 0.5f - (SCREEN_WIDTH * 0.2f) / 2.f, SCREEN_HEIGHT * 0.30f + SCREEN_HEIGHT * 0.165f, 0.f));
			texProgram.setUniformMatrix4f("modelview", modelview);
			if (button == 1) tq_button_1_main_menu->render(texs[3]);
			else tq_button_1_main_menu->render(t_button_0_main_menu);
			modelview = glm::translate(glm::mat4(1.0f), glm::vec3(SCREEN_WIDTH * 0.5f - (SCREEN_WIDTH * 0.2f) / 2.f, SCREEN_HEIGHT * 0.30f + SCREEN_HEIGHT * 0.330f, 0.f));
			texProgram.setUniformMatrix4f("modelview", modelview);
			if (button == 2) tq_button_2_main_menu->render(texs[3]);
			else tq_button_2_main_menu->render(t_button_0_main_menu);
			modelview = glm::translate(glm::mat4(1.0f), glm::vec3(SCREEN_WIDTH * 0.5f - (SCREEN_WIDTH * 0.2f) / 2.f, SCREEN_HEIGHT * 0.30f + SCREEN_HEIGHT * 0.495f, 0.f));
			texProgram.setUniformMatrix4f("modelview", modelview);
			if (button == 3) tq_button_3_main_menu->render(texs[3]);
			else tq_button_3_main_menu->render(t_button_0_main_menu);
			break;
			}
		case 3:
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
		case 4:
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
		case 2:
			texProgram.use();
			projection = glm::ortho(camera_movement, float(SCREEN_WIDTH - 1 + camera_movement), float(SCREEN_HEIGHT - 1), 0.f);
			texProgram.setUniformMatrix4f("projection", projection);
			texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
			modelview = glm::mat4(1.0f);
			texProgram.setUniformMatrix4f("modelview", modelview);
			texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

			levels[currentLevel]->render(texProgram);
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


