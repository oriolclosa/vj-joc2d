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
#define MAX_ENEMIES 100 //For 100

#define PROB_COINS 1 //For 1.000

#define POS_SKY_X 16
#define POS_SKY_Y 0

#define POS_INFO_X 20
#define POS_INFO_Y 330

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


void Level::init(ShaderProgram &texProgram){
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
	backTextures[6].loadFromFile("images/margaret/exteriorgrass.png", TEXTURE_PIXEL_FORMAT_RGBA);
	backTextures[6].setMagFilter(GL_NEAREST);
	backTextures[7].loadFromFile("images/margaret/exteriorfloorsewer.png", TEXTURE_PIXEL_FORMAT_RGBA);
	backTextures[7].setMagFilter(GL_NEAREST);
	backSprites[0] = Sprite::createSprite(glm::vec2(32, 32), glm::vec2(1, 1), &backTextures[0], &texProgram);
	backSprites[1] = Sprite::createSprite(glm::vec2(32, 32), glm::vec2(1, 1), &backTextures[1], &texProgram);
	backSprites[2] = Sprite::createSprite(glm::vec2(32, 32), glm::vec2(1, 1), &backTextures[2], &texProgram);
	backSprites[3] = Sprite::createSprite(glm::vec2(32, 32), glm::vec2(1, 1), &backTextures[3], &texProgram);
	backSprites[4] = Sprite::createSprite(glm::vec2(32, 32), glm::vec2(1, 1), &backTextures[4], &texProgram);
	backSprites[5] = Sprite::createSprite(glm::vec2(32, 32), glm::vec2(1, 1), &backTextures[5], &texProgram);
	backSprites[6] = Sprite::createSprite(glm::vec2(32, 32), glm::vec2(1, 1), &backTextures[6], &texProgram);
	backSprites[7] = Sprite::createSprite(glm::vec2(32, 32), glm::vec2(1, 1), &backTextures[7], &texProgram);

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
	}
	sprBuildings[0] = Sprite::createSprite(glm::vec2(256, 160), glm::vec2(1, 1), &texBuildings[0], &texProgram);
	sprBuildings[1] = Sprite::createSprite(glm::vec2(256, 224), glm::vec2(1, 1), &texBuildings[1], &texProgram);
	sprBuildings[2] = Sprite::createSprite(glm::vec2(192, 192), glm::vec2(1, 1), &texBuildings[2], &texProgram);
	sprBuildings[3] = Sprite::createSprite(glm::vec2(256, 160), glm::vec2(1, 1), &texBuildings[3], &texProgram);

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
	sprObject[6] = Sprite::createSprite(glm::vec2(96, 128), glm::vec2(1, 1), &texObject[6], &texProgram);
	sprObject[7] = Sprite::createSprite(glm::vec2(32, 96), glm::vec2(1, 1), &texObject[7], &texProgram);

	//Walkable areas
	walkableTexture.loadFromFile("images/margaret/ok.png", TEXTURE_PIXEL_FORMAT_RGBA);
	walkableTexture.setMagFilter(GL_NEAREST);
	walkableSprite = Sprite::createSprite(glm::vec2(16, 16), glm::vec2(1, 1), &walkableTexture, &texProgram);
	
	//Player
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);

	//Enemies and coins
	int tile;
	num_enemies = 0, num_coins = 0;
	for (int j = 0; j < map->getMapSize().y; j++) {
		for (int i = 0; i < map->getMapSize().x; i++) {
			tile = map->getMap()[j * map->getMapSize().x + i];
			if ((tile == '3') && (num_enemies < MAX_ENEMIES)) {
				int enemy = rand() % 100;
				if (enemy <= PROB_ENEMIES) {
					glm::vec2 posTile = glm::vec2(SCREEN_X + i * 16, SCREEN_Y + j * 16);
					enemies[num_enemies] = new Enemy();
					enemies[num_enemies]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, posTile);
					enemies[num_enemies]->setTileMap(map);
					enemies[num_enemies]->setPlayer(player);
					enemies[num_enemies]->setPlayerPos(player->getPosition());
					++num_enemies;
				}
			}
			else if ((tile == '2') && (num_coins < MAX_COINS)) {
				int coin = rand() % 1000;
				if (coin <= PROB_ENEMIES) {
					glm::vec2 posTile = glm::vec2(SCREEN_X + i * 16, SCREEN_Y + j * 16);
					coins[num_coins] = new Coin();
					coins[num_coins]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, posTile);
					coins[num_coins]->setPosition(posTile);
					coins[num_coins]->setPlayer(player);
					++num_coins;
				}
			}
		}
	}

	//Infohealth
	texInfoHealth.loadFromFile("images/margaret/infohealth.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texInfoHealth.setMagFilter(GL_NEAREST);
	sprInfoHealth = Sprite::createSprite(glm::vec2(99, 32), glm::vec2(1.0f, 1.0f/53.0f), &texInfoHealth, &texProgram);
	sprInfoHealth->setNumberAnimations(53);
	for (int i = 0; i < 53; ++i) {
		sprInfoHealth->addKeyframe(i, glm::vec2(1.0f, (float(i)/53.0f)));
	}
	sprInfoHealth->changeAnimation(52);
	sprInfoHealth->setPosition(glm::vec2(SCREEN_X + POS_INFO_X, SCREEN_Y + POS_INFO_Y));

	//Infolifes
	for (int i = 0; i < 3; ++i) {
		ostringstream path;
		path << "images/margaret/infolifes" << (i + 1) << ".png";
		texInfoLifes[i].loadFromFile(path.str(), TEXTURE_PIXEL_FORMAT_RGBA);
		texInfoLifes[i].setMagFilter(GL_NEAREST);
		sprInfoLifes[i] = Sprite::createSprite(glm::vec2(32, 32), glm::vec2(1.0f, 1.0f), &texInfoLifes[i], &texProgram);
		sprInfoLifes[i]->setPosition(glm::vec2(SCREEN_X + POS_INFO_X, SCREEN_Y + POS_INFO_Y));
	}

	//Text
	if (!text.init("fonts/OpenSans-Regular.ttf"))
		if (!text.init("fonts/OpenSans-Bold.ttf"))
			if (!text.init("fonts/DroidSerif.ttf"))
				cout << "Could not load font!!!" << endl;
	score = 0;
	active = true;
	currentTime = 0.0f;
}

void Level::update(int deltaTime) {
	if (active) {
		currentTime += deltaTime;
		player->update(deltaTime);
		if (active) {
			for (int i = 0; i < num_enemies; ++i) {
				if (enemies[i] != NULL) {
					enemies[i]->setPlayerPos(player->getPosition());
					enemies[i]->update(deltaTime);
				}
			}
			for (int i = 0; i < num_coins; ++i) {
				if (coins[i] != NULL) {
					coins[i]->update(deltaTime);
				}
			}
			updateInfoHealth(player->getHealth());
		    updatePlayerAttack(player->getDamageDone());
		}
	}
}

void Level::render(ShaderProgram &texProgram) {
	if (active) {
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
				else if (tile >= '7' && tile <= '8') {
					int tileAux = tile - int('1');
					glm::vec2 posTile = glm::vec2(SCREEN_X + i * 32, SCREEN_Y + j * 32);
					backSprites[tileAux]->setPosition(posTile);
					backSprites[tileAux]->render();
				}
			}
		}
		glm::vec2 playerPos = player->getPosition();
		int playerPosX = ((playerPos.x + 16.0f) / 32.0f);
		int playerPosY = ((playerPos.y - 32.0f) / 32.0f);
		for (int i = 0; i < spriteMap->getMapSize().x; i++) {
			for (int j = 0; j < spriteMap->getMapSize().y; j++) {
				tile = spriteMap->getMap()[j * spriteMap->getMapSize().x + i];
				glm::vec2 posTile = glm::vec2(SCREEN_X + i * 32, SCREEN_Y + j * 32);
				if (tile >= '1' && tile <= ':') {
					int tileAux = tile - int('1');
					sprWall[tileAux]->setPosition(posTile);
					sprWall[tileAux]->render();
				}
				else if (tile >= 'a' && tile <= 'h') {
					int tileAux = tile - int('a');
					sprObject[tileAux]->setPosition(posTile);
					sprObject[tileAux]->render();
				}
				else if (tile >= 'A' && tile <= 'D') {
					int tileAux = tile - int('A');
					sprBuildings[tileAux]->setPosition(posTile);
					sprBuildings[tileAux]->render();
				}
				if ((playerPosX == (i) || playerPosX == (i - 1) || playerPosX == (i + 1)) && playerPosY == (j)) {
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
		for (int i = 0; i < num_coins; ++i) {
			if (coins[i] != NULL) {
				float distance = sqrt(pow(coins[i]->getPosition().x - player->getPosition().x, 2) + pow(coins[i]->getPosition().y - player->getPosition().y, 2));
				if (distance <= 32) {
					coins[i] = NULL;
					score += 10;
				}
				else {
					coins[i]->render();
				}
			}
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

		sprInfoHealth->render();
		sprInfoLifes[((player->getLifes()) - 1)]->render();
		ostringstream scoreText;
		scoreText << "Score: " << score;
		if(text.init()){
			//text.render(scoreText.str(), glm::vec2(POS_INFO_X + 35.0f, SCREEN_Y + POS_INFO_Y + 8.0f), 12, glm::vec4(1, 1, 1, 1));
		}
	}
}

glm::vec2 Level::getPlayerPos() {
	return player->getPosition();
}

void Level::updateInfoHealth(float health) {
	int healthAux = int(52.0f*(health / 100.f));
	if (healthAux < 0) {
		healthAux = 0;
	}
	else if (healthAux > 52) {
		healthAux = 52;
	}
	sprInfoHealth->changeAnimation(healthAux);
	float posAux = (getPlayerPos().x - SCREEN_WIDTH / 2);
	if (posAux < 0.0f) {
		posAux = 0.0f;
	}
	sprInfoHealth->setPosition(glm::vec2(posAux + POS_INFO_X, POS_INFO_Y));
	sprInfoLifes[((player->getLifes()) - 1)]->setPosition(glm::vec2(posAux + POS_INFO_X, POS_INFO_Y));
}

void Level::updatePlayerAttack(float damage) {
	if (damage == 0) return;
	bool right = player->getDirection();
	float x_player = getPlayerPos().x;
	for (int i = 0; i < num_enemies; ++i) {
		float x_enemy = enemies[i]->getPosition().x;
		float dif = abs(x_player - x_enemy);
		if (!right && x_enemy >= x_player && dif <= 64) {
			enemies[i]->takeDamage(damage);
		}
		else if (right && x_enemy <= x_player && dif <= 64) {
			enemies[i]->takeDamage(damage);
		}
	}
}

int Level::getPlayerLifes() {
	return player->getLifes();
}

void Level::setActive(bool activeAux) {
	active = activeAux;
}

void Level::restart() {
	skySprite->setPosition(glm::vec2(POS_SKY_X * 32, POS_SKY_Y * 32));
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));

	//Enemies and coins
	for (int i = 0; i < num_enemies; ++i) {
		if (enemies[i] != NULL) {
			enemies[i]->restart();
		}
	}
	for (int i = 0; i < num_coins; ++i) {
		if (coins[i] != NULL) {
			coins[i]->restart();
		}
	}

	//Infohealth
	sprInfoHealth->changeAnimation(52);
	sprInfoHealth->setPosition(glm::vec2(SCREEN_X + POS_INFO_X, SCREEN_Y + POS_INFO_Y));

	//Infolifes
	sprInfoLifes[2]->setPosition(glm::vec2(SCREEN_X + POS_INFO_X, SCREEN_Y + POS_INFO_Y));

	//Text
	if (!text.init("fonts/OpenSans-Regular.ttf"))
		if (!text.init("fonts/OpenSans-Bold.ttf"))
			if (!text.init("fonts/DroidSerif.ttf"))
				cout << "Could not load font!!!" << endl;

	score = 0;
	active = true;
	currentTime = 0.0f;
}