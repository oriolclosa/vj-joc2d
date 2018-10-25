#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include <string>
#include <set>
#include <algorithm>
#include <sstream>


#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 6


Scene::Scene() {
	map = NULL;
	spritemap = NULL;
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
	camera_movement = 0.0f;

	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	backgroundMap = TileMap::createTileMap("levels/level01-background.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	spriteMap = TileMap::createTileMap("levels/level01-sprites.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	overgroundMap = TileMap::createTileMap("levels/level01-overground.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);

	backTextures[0].loadFromFile("images/margaret/wall.png", TEXTURE_PIXEL_FORMAT_RGBA);
	backTextures[0].setMagFilter(GL_NEAREST);
	backTextures[1].loadFromFile("images/margaret/floor.png", TEXTURE_PIXEL_FORMAT_RGBA);
	backTextures[1].setMagFilter(GL_NEAREST);
	backTextures[2].loadFromFile("images/margaret/wallfloor.png", TEXTURE_PIXEL_FORMAT_RGBA);
	backTextures[2].setMagFilter(GL_NEAREST);
	backSprites[0] = Sprite::createSprite(glm::vec2(32, 32), glm::vec2(1, 1), &backTextures[0], &texProgram);
	backSprites[1] = Sprite::createSprite(glm::vec2(32, 32), glm::vec2(1, 1), &backTextures[1], &texProgram);
	backSprites[2] = Sprite::createSprite(glm::vec2(32, 32), glm::vec2(1, 1), &backTextures[2], &texProgram);

	//Overground
	for (int i = 0; i <=17; ++i) {
		ostringstream path;
		path << "images/margaret/wallover" << (i+1) << ".png";
		overTextures[i].loadFromFile(path.str(), TEXTURE_PIXEL_FORMAT_RGBA);
		overTextures[i].setMagFilter(GL_NEAREST);
		overSprites[i] = Sprite::createSprite(glm::vec2(32, 32), glm::vec2(1, 1), &overTextures[i], &texProgram);
	}

	//Wall pictures
	for (int i = 0; i <= 10; ++i) {
		ostringstream path;
		path << "images/margaret/picture" << (i + 1) << ".png";
		texWall[i].loadFromFile(path.str(), TEXTURE_PIXEL_FORMAT_RGBA);
		texWall[i].setMagFilter(GL_NEAREST);
		sprWall[i] = Sprite::createSprite(glm::vec2(96, 96), glm::vec2(1, 1), &texWall[i], &texProgram);
	}

	//Objects
	for (int i = 0; i <= 10; ++i) {
		ostringstream path;
		path << "images/margaret/object" << (i + 1) << ".png";
		texObject[i].loadFromFile(path.str(), TEXTURE_PIXEL_FORMAT_RGBA);
		texObject[i].setMagFilter(GL_NEAREST);
	}
	sprObject[0] = Sprite::createSprite(glm::vec2(32, 64), glm::vec2(1, 1), &texObject[0], &texProgram);
	sprObject[1] = Sprite::createSprite(glm::vec2(96, 64), glm::vec2(1, 1), &texObject[1], &texProgram);
	sprObject[2] = Sprite::createSprite(glm::vec2(32, 64), glm::vec2(1, 1), &texObject[2], &texProgram);
	sprObject[3] = Sprite::createSprite(glm::vec2(32, 64), glm::vec2(1, 1), &texObject[3], &texProgram);
	sprObject[4] = Sprite::createSprite(glm::vec2(32, 64), glm::vec2(1, 1), &texObject[4], &texProgram);
	sprObject[5] = Sprite::createSprite(glm::vec2(32, 96), glm::vec2(1, 1), &texObject[5], &texProgram);

	//Walkable areas
	walkableTexture.loadFromFile("images/margaret/ok.png", TEXTURE_PIXEL_FORMAT_RGBA);
	walkableTexture.setMagFilter(GL_NEAREST);
	walkableSprite = Sprite::createSprite(glm::vec2(32, 32), glm::vec2(1, 1), &walkableTexture, &texProgram);

	/*textures[1].loadFromFile("images/margaret/object1-animated.png", TEXTURE_PIXEL_FORMAT_RGBA);
	textures[1].setMagFilter(GL_NEAREST);
	textures[2].loadFromFile("images/margaret/object2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	textures[2].setMagFilter(GL_NEAREST);
	textures[3].loadFromFile("images/margaret/desk1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	textures[3].setMagFilter(GL_NEAREST);
	textures[4].loadFromFile("images/margaret/desk2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	textures[4].setMagFilter(GL_NEAREST);
	textures[5].loadFromFile("images/margaret/desk3.png", TEXTURE_PIXEL_FORMAT_RGBA);
	textures[5].setMagFilter(GL_NEAREST);
	textures[6].loadFromFile("images/margaret/desk4.png", TEXTURE_PIXEL_FORMAT_RGBA);
	textures[6].setMagFilter(GL_NEAREST);
	textures[7].loadFromFile("images/margaret/desk5.png", TEXTURE_PIXEL_FORMAT_RGBA);
	textures[7].setMagFilter(GL_NEAREST);
	textures[8].loadFromFile("images/margaret/desk6.png", TEXTURE_PIXEL_FORMAT_RGBA);
	textures[8].setMagFilter(GL_NEAREST);
	textures[9].loadFromFile("images/margaret/plant1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	textures[9].setMagFilter(GL_NEAREST);
	sprites[1] = Sprite::createSprite(glm::vec2(32, 64), glm::vec2(0.125, 1), &textures[1], &texProgram);
	sprites[1]->setNumberAnimations(1);
	sprites[1]->setAnimationSpeed(0, 6);
	sprites[1]->addKeyframe(0, glm::vec2(0.0f, 0.0f));
	sprites[1]->addKeyframe(0, glm::vec2(0.125f, 0.0f));
	sprites[1]->addKeyframe(0, glm::vec2(0.25f, 0.0f));
	sprites[1]->addKeyframe(0, glm::vec2(0.375f, 0.0f));
	sprites[1]->addKeyframe(0, glm::vec2(0.5f, 0.0f));
	sprites[1]->addKeyframe(0, glm::vec2(0.625f, 0.0f));
	sprites[1]->addKeyframe(0, glm::vec2(0.75f, 0.0f));
	sprites[1]->addKeyframe(0, glm::vec2(0.875f, 0.0f));
	sprites[1]->changeAnimation(0);
	sprites[2] = Sprite::createSprite(glm::vec2(64, 64), glm::vec2(1, 1), &textures[2], &texProgram);
	sprites[3] = Sprite::createSprite(glm::vec2(64, 64), glm::vec2(1, 1), &textures[3], &texProgram);
	sprites[4] = Sprite::createSprite(glm::vec2(64, 64), glm::vec2(1, 1), &textures[4], &texProgram);
	sprites[5] = Sprite::createSprite(glm::vec2(64, 64), glm::vec2(1, 1), &textures[5], &texProgram);
	sprites[6] = Sprite::createSprite(glm::vec2(64, 64), glm::vec2(1, 1), &textures[6], &texProgram);
	sprites[7] = Sprite::createSprite(glm::vec2(64, 64), glm::vec2(1, 1), &textures[7], &texProgram);
	sprites[8] = Sprite::createSprite(glm::vec2(64, 64), glm::vec2(1, 1), &textures[8], &texProgram);
	sprites[9] = Sprite::createSprite(glm::vec2(32, 64), glm::vec2(1, 1), &textures[9], &texProgram);

	//Object 1
	set<int> numDesks = { 1, 2, 3, 4, 5, 6 };
	for (int i = 0; i < 5; ++i) {
		set<int>::iterator actDesk = numDesks.begin();
		advance(actDesk, rand()%numDesks.size());
		string path = "images/margaret/desk" + to_string(*actDesk);
		path += ".png";
		//numDesks.erase(actDesk);
		texDesk[i].loadFromFile(path, TEXTURE_PIXEL_FORMAT_RGBA);
		texDesk[i].setMagFilter(GL_NEAREST);
		sprDesk[i] = Sprite::createSprite(glm::vec2(64, 64), glm::vec2(1, 1), &texDesk[i], &texProgram);
	}*/
	
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	projection = glm::ortho(0.0f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime) {
	currentTime += deltaTime;
	//sprites[1]->update(deltaTime);
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
			projection = glm::ortho(camera_movement, float(SCREEN_WIDTH -1 + camera_movement), float(SCREEN_HEIGHT - 1), 0.f);
			texProgram.setUniformMatrix4f("projection", projection);
			texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
			modelview = glm::mat4(1.0f);
			texProgram.setUniformMatrix4f("modelview", modelview);
			texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

			int tile;
			for (int j = 0; j < backgroundMap->getMapSize().y; j++) {
				for (int i = 0; i < backgroundMap->getMapSize().x; i++) {
					tile = backgroundMap->getMap()[j * backgroundMap->getMapSize().x + i];
					if (tile >= '0' && tile <= '2') {
						int tileAux = tile - int('0');
						glm::vec2 posTile = glm::vec2(SCREEN_X + i * 32, SCREEN_Y + j * 32);
						backSprites[tileAux]->setPosition(posTile);
						backSprites[tileAux]->render();
					}
				}
			}
			for (int j = 0; j < spriteMap->getMapSize().y; j++) {
				for (int i = 0; i < spriteMap->getMapSize().x; i++) {
					tile = spriteMap->getMap()[j * spriteMap->getMapSize().x + i];
					glm::vec2 posTile = glm::vec2(SCREEN_X + i * 32, SCREEN_Y + j * 32);
					if (tile >= '1' && tile <= ':') {
						int tileAux = tile - int('1');
						sprWall[tileAux]->setPosition(posTile);
						sprWall[tileAux]->render();
					}
					else if (tile >= 'a' && tile <= 'j') {
						int tileAux = tile - int('a');
						sprObject[tileAux]->setPosition(posTile);
						sprObject[tileAux]->render();
					}
				}
			}
			player->render();
			for (int j = 0; j < overgroundMap->getMapSize().y; j++) {
				for (int i = 0; i < overgroundMap->getMapSize().x; i++) {
					tile = overgroundMap->getMap()[j * overgroundMap->getMapSize().x + i];
					if (tile >= '1' && tile <= 'A') {
						int tileAux = tile - int('1');
						glm::vec2 posTile = glm::vec2(SCREEN_X + i * 32, SCREEN_Y + j * 32);
						overSprites[tileAux]->setPosition(posTile);
						overSprites[tileAux]->render();
					}
				}
			}
			if (Game::instance().getWalkable()) {
				for (int j = 0; j < map->getMapSize().y; j++) {
					for (int i = 0; i < map->getMapSize().x; i++) {
						tile = map->getMap()[j * map->getMapSize().x + i];
						if (tile == '1') {
							glm::vec2 posTile = glm::vec2(SCREEN_X + i * 32, SCREEN_Y + j * 32);
							walkableSprite->setPosition(posTile);
							walkableSprite->render();
						}
					}
				}
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
	if (movement < 0.0f){
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



