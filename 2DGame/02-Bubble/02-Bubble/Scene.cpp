#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"



#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 25


Scene::Scene() {
	map = NULL;
	assetmap = NULL;
	player = NULL;
}

Scene::~Scene() {
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
}


void Scene::init() {
	initShaders();

	// Menu_0
	glm::vec2 geom[2];
	glm::vec2 texCoords[2];
	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	texQuad[0] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	texs[0].loadFromFile("images/wp_placeholder_menu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texs[0].setMagFilter(GL_NEAREST);
	// Select which font you want to use
	if(!text.init("fonts/OpenSans-Regular.ttf"))
		if(!text.init("fonts/OpenSans-Bold.ttf"))
			if(!text.init("fonts/DroidSerif.ttf"))
				cout << "Could not load font!!!" << endl;
	// Menu_1
	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.15f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	texQuad[2] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.15f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	texQuad[3] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.15f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	texQuad[4] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.15f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	texQuad[5] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	texs[2].loadFromFile("images/menu_0.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texs[2].setMagFilter(GL_NEAREST);
	texs[3].loadFromFile("images/menu_1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texs[3].setMagFilter(GL_NEAREST);
	// Exemple
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	assetmap = TileMap::createTileMap("levels/level01-assets.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime) {
	currentTime += deltaTime;
	player->update(deltaTime);
}

void Scene::render() {
	glm::mat4 modelview;
	// TODO: crear metodes per cada scena
	switch(Game::instance().getRenderScene()) {
		case 0:
			// Menu_0
			texProgram.use();
			texProgram.setUniformMatrix4f("projection", projection);
			texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

			modelview = glm::mat4(1.0f);
			texProgram.setUniformMatrix4f("modelview", modelview);
			texQuad[0]->render(texs[0]);
			text.render("Untitled 2D Game", glm::vec2(SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.225f), 64, glm::vec4(1, 1, 1, 1));
			text.render("Press F to start the game", glm::vec2(SCREEN_WIDTH * 0.375f, SCREEN_HEIGHT * 0.85f), 24, glm::vec4(1, 1, 1, 1));
			break;
		case 1:
			// Menu_1
			{
			texProgram.use();
			texProgram.setUniformMatrix4f("projection", projection);
			texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
			modelview = glm::mat4(1.0f);
			texProgram.setUniformMatrix4f("modelview", modelview);
			texQuad[0]->render(texs[0]);
			text.render("Untitled 2D Game", glm::vec2(SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.225f), 64, glm::vec4(1, 1, 1, 1));

			int button = Game::instance().getSelectedMainButton();
			texProgram.use();
			modelview = glm::translate(glm::mat4(1.0f), glm::vec3(SCREEN_WIDTH * 0.5f - (SCREEN_WIDTH * 0.2f) / 2.f, SCREEN_HEIGHT * 0.30f, 0.f));
			texProgram.setUniformMatrix4f("modelview", modelview);
			if (button == 1) texQuad[2]->render(texs[3]);
			else texQuad[2]->render(texs[2]);
			modelview = glm::translate(glm::mat4(1.0f), glm::vec3(SCREEN_WIDTH * 0.5f - (SCREEN_WIDTH * 0.2f) / 2.f, SCREEN_HEIGHT * 0.30f + SCREEN_HEIGHT * 0.165f, 0.f));
			texProgram.setUniformMatrix4f("modelview", modelview);
			if (button == 2) texQuad[3]->render(texs[3]);
			else texQuad[3]->render(texs[2]);
			modelview = glm::translate(glm::mat4(1.0f), glm::vec3(SCREEN_WIDTH * 0.5f - (SCREEN_WIDTH * 0.2f) / 2.f, SCREEN_HEIGHT * 0.30f + SCREEN_HEIGHT * 0.330f, 0.f));
			texProgram.setUniformMatrix4f("modelview", modelview);
			if (button == 3) texQuad[4]->render(texs[3]);
			else texQuad[4]->render(texs[2]);
			modelview = glm::translate(glm::mat4(1.0f), glm::vec3(SCREEN_WIDTH * 0.5f - (SCREEN_WIDTH * 0.2f) / 2.f, SCREEN_HEIGHT * 0.30f + SCREEN_HEIGHT * 0.495f, 0.f));
			texProgram.setUniformMatrix4f("modelview", modelview);
			if (button == 4) texQuad[5]->render(texs[3]);
			else texQuad[5]->render(texs[2]);
			break;
			}
		case 2:
			//Exemple
			texProgram.use();
			texProgram.setUniformMatrix4f("projection", projection);
			texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
			modelview = glm::mat4(1.0f);
			texProgram.setUniformMatrix4f("modelview", modelview);
			texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
			map->render();
			assetmap->render();
			player->render();
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



