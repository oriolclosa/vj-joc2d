#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include <string>
#include <set>
#include <algorithm>
#include <sstream>


#define INIT_PLAYER_X_TILES 8
#define INIT_PLAYER_Y_TILES 12

#define PROB_ENEMIES 10
#define MAX_ENEMIES 100

#define POS_SKY_X 16
#define POS_SKY_Y 0


Level::Level() {
	map = NULL;
	spritemap = NULL;
	player = NULL;
}

Level::~Level() {
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
}


void Level::init(ShaderProgram &texProgramAux, glm::mat4 &projectionAux){
	texProgram = texProgramAux;
	projection = projectionAux;

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
	backTextures[3].loadFromFile("images/margaret/exteriorfloor.png", TEXTURE_PIXEL_FORMAT_RGBA);
	backTextures[3].setMagFilter(GL_NEAREST);
	backTextures[4].loadFromFile("images/margaret/exteriorfence.png", TEXTURE_PIXEL_FORMAT_RGBA);
	backTextures[4].setMagFilter(GL_NEAREST);
	backTextures[5].loadFromFile("images/margaret/exteriorwallfloor.png", TEXTURE_PIXEL_FORMAT_RGBA);
	backTextures[5].setMagFilter(GL_NEAREST);
	backSprites[0] = Sprite::createSprite(glm::vec2(32, 32), glm::vec2(1, 1), &backTextures[0], &texProgram);
	backSprites[1] = Sprite::createSprite(glm::vec2(32, 32), glm::vec2(1, 1), &backTextures[1], &texProgram);
	backSprites[2] = Sprite::createSprite(glm::vec2(32, 32), glm::vec2(1, 1), &backTextures[2], &texProgram);
	backSprites[3] = Sprite::createSprite(glm::vec2(32, 32), glm::vec2(1, 1), &backTextures[3], &texProgram);
	backSprites[4] = Sprite::createSprite(glm::vec2(32, 32), glm::vec2(1, 1), &backTextures[4], &texProgram);
	backSprites[5] = Sprite::createSprite(glm::vec2(32, 32), glm::vec2(1, 1), &backTextures[5], &texProgram);

	//Sky
	skyTexture.loadFromFile("images/margaret/sky.png", TEXTURE_PIXEL_FORMAT_RGBA);
	skyTexture.setMagFilter(GL_NEAREST);
	skySprite = Sprite::createSprite(glm::vec2(1024, 128), glm::vec2(1, 1), &skyTexture, &texProgram);
	skySprite->setPosition(glm::vec2(POS_SKY_X * 32, POS_SKY_Y * 32));

	//Buildings
	for (int i = 0; i <= 5; ++i) {
		ostringstream path;
		path << "images/margaret/building" << (i + 1) << ".png";
		texBuildings[i].loadFromFile(path.str(), TEXTURE_PIXEL_FORMAT_RGBA);
		texBuildings[i].setMagFilter(GL_NEAREST);
		sprBuildings[i] = Sprite::createSprite(glm::vec2(256, 160), glm::vec2(1, 1), &texBuildings[i], &texProgram);
	}

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
	walkableSprite = Sprite::createSprite(glm::vec2(16, 16), glm::vec2(1, 1), &walkableTexture, &texProgram);
	
	//Player
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);

	//Enemies
	int tile;
	num_enemies = 0;
	for (int j = 0; j < map->getMapSize().y; j++) {
		for (int i = 0; i < map->getMapSize().x; i++) {
			tile = map->getMap()[j * map->getMapSize().x + i];
			if ((tile == '3') && (num_enemies < MAX_ENEMIES)) {
				int enemy = rand() % 100;
				cout << enemy << endl;
				if (enemy <= PROB_ENEMIES) {
					glm::vec2 posTile = glm::vec2(SCREEN_X + i * 16, SCREEN_Y + j * 16);
					enemies[num_enemies] = new Enemy();
					enemies[num_enemies]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
					enemies[num_enemies]->setPosition(posTile);
					enemies[num_enemies]->setTileMap(map);
					enemies[num_enemies]->setPlayerPos(player->getPosition());
					++num_enemies;
				}
			}
		}
	}
	
	projection = glm::ortho(0.0f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Level::update(int deltaTime) {
	currentTime += deltaTime;
	player->update(deltaTime);
	for (int i = 0; i < num_enemies; ++i) {
		enemies[i]->setPlayerPos(player->getPosition());
		enemies[i]->update(deltaTime);
	}
}

void Level::render() {
	skySprite->render();
	int tile;
	for (int j = 0; j < backgroundMap->getMapSize().y; j++) {
		for (int i = 0; i < backgroundMap->getMapSize().x; i++) {
			tile = backgroundMap->getMap()[j * backgroundMap->getMapSize().x + i];
			if (tile >= '0' && tile <= '5') {
				int tileAux = tile - int('0');
				glm::vec2 posTile = glm::vec2(SCREEN_X + i * 32, SCREEN_Y + j * 32);
				backSprites[tileAux]->setPosition(posTile);
				backSprites[tileAux]->render();
			}
		}
	}
	glm::vec2 playerPos = player->getPosition();
	int playerPosX = (playerPos.x / 32.0f) - SCREEN_X - 1;
	int playerPosY = (playerPos.y / 32.0f) - SCREEN_Y - 1;
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
			else if (tile >= 'A' && tile <= 'A') {
				int tileAux = tile - int('A');
				sprBuildings[tileAux]->setPosition(posTile);
				sprBuildings[tileAux]->render();
			}
			if (playerPosX == i && playerPosY == j) {
				player->render();
			}
		}
	}
	/*for (int i = 0; i < num_enemies; ++i) {
		enemies1Sprite[i]->render();
	}*/
	for (int i = 0; i < num_enemies; ++i) {
		enemies[i]->render();
	}
	//player->render();
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
				if (tile != '0') {
					glm::vec2 posTile = glm::vec2(SCREEN_X + i * 16, SCREEN_Y + j * 16);
					walkableSprite->setPosition(posTile);
					walkableSprite->render();
				}
			}
		}
	}
}

glm::vec2 Level::getPlayerPos() {
	return player->getPosition();
}



