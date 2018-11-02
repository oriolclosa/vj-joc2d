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


#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 8

#define PROB_ENEMIES 50 //For 100
#define MAX_ENEMIES 100

#define PROB_COINS 10 //For 1.000

#define POS_SKY_X 16
#define POS_SKY_Y 0

#define POS_INFO_X 20
#define POS_INFO_Y 330

enum character{
	SKLODOWSKA, TESLA
};

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


void Level::init(ShaderProgram &texProgram, int lvl){
	currentCharacter = Game::instance().getSelectedCharacter();
	cout << currentCharacter << endl;

	ostringstream pathlvl1;
	pathlvl1 << "levels/level0" << lvl << ".txt";
	map = TileMap::createTileMap(pathlvl1.str(), glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	ostringstream pathlvl2;
	pathlvl2 << "levels/level0" << lvl << "-background.txt";
	backgroundMap = TileMap::createTileMap(pathlvl2.str(), glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	ostringstream pathlvl3;
	pathlvl3 << "levels/level0" << lvl << "-sprites.txt";
	spriteMap = TileMap::createTileMap(pathlvl3.str(), glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	ostringstream pathlvl4;
	pathlvl4 << "levels/level0" << lvl << "-overground.txt";
	overgroundMap = TileMap::createTileMap(pathlvl4.str(), glm::vec2(SCREEN_X, SCREEN_Y), texProgram);

	//Background
	for (int i = 0; i < 10; ++i) {
		ostringstream path;
		path << "images/" << currentCharacter << "/back" << (i + 1) << ".png";
		cout << path.str() << endl;
		backTextures[i].loadFromFile(path.str(), TEXTURE_PIXEL_FORMAT_RGBA);
		backTextures[i].setMagFilter(GL_NEAREST);
		backSprites[i] = Sprite::createSprite(glm::vec2(32, 32), glm::vec2(1, 1), &backTextures[i], &texProgram);
	}

	//Sky
	ostringstream path;
	path << "images/" << currentCharacter << "/sky.png";
	skyTexture.loadFromFile(path.str(), TEXTURE_PIXEL_FORMAT_RGBA);
	skyTexture.setMagFilter(GL_NEAREST);
	skySprite = Sprite::createSprite(glm::vec2(1024, 128), glm::vec2(1, 1), &skyTexture, &texProgram);
	skySprite->setPosition(glm::vec2(POS_SKY_X * 32, POS_SKY_Y * 32));

	//Buildings
	for (int i = 0; i <= 5; ++i) {
		ostringstream path;
		path << "images/" << currentCharacter << "/building" << (i + 1) << ".png";
		texBuildings[i].loadFromFile(path.str(), TEXTURE_PIXEL_FORMAT_RGBA);
		texBuildings[i].setMagFilter(GL_NEAREST);
	}
	sprBuildings[0] = Sprite::createSprite(glm::vec2(256, 160), glm::vec2(1, 1), &texBuildings[0], &texProgram);
	sprBuildings[1] = Sprite::createSprite(glm::vec2(256, 224), glm::vec2(1, 1), &texBuildings[1], &texProgram);
	sprBuildings[2] = Sprite::createSprite(glm::vec2(192, 192), glm::vec2(1, 1), &texBuildings[2], &texProgram);
	sprBuildings[3] = Sprite::createSprite(glm::vec2(256, 160), glm::vec2(1, 1), &texBuildings[3], &texProgram);
	sprBuildings[4] = Sprite::createSprite(glm::vec2(192, 192), glm::vec2(1, 1), &texBuildings[4], &texProgram);

	//Overground
	for (int i = 0; i <=17; ++i) {
		ostringstream path;
		path << "images/" << currentCharacter << "/wallover" << (i + 1) << ".png";
		overTextures[i].loadFromFile(path.str(), TEXTURE_PIXEL_FORMAT_RGBA);
		overTextures[i].setMagFilter(GL_NEAREST);
		overSprites[i] = Sprite::createSprite(glm::vec2(32, 32), glm::vec2(1, 1), &overTextures[i], &texProgram);
	}

	//Wall pictures
	for (int i = 0; i <= 10; ++i) {
		ostringstream path;
		path << "images/" << currentCharacter << "/picture" << (i + 1) << ".png";
		texWall[i].loadFromFile(path.str(), TEXTURE_PIXEL_FORMAT_RGBA);
		texWall[i].setMagFilter(GL_NEAREST);
		sprWall[i] = Sprite::createSprite(glm::vec2(96, 96), glm::vec2(1, 1), &texWall[i], &texProgram);
	}

	//Objects
	for (int i = 0; i <= 10; ++i) {
		ostringstream path;
		path << "images/" << currentCharacter << "/object" << (i + 1) << ".png";
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
	ostringstream path2;
	path2 << "images/" << currentCharacter << "/ok.png";
	walkableTexture.loadFromFile(path2.str(), TEXTURE_PIXEL_FORMAT_RGBA);
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
					glm::vec2 posTile = glm::vec2(SCREEN_X + i * 16, SCREEN_Y + j * 16 - 96);
					enemies[num_enemies] = new Enemy();
					enemies[num_enemies]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, posTile, rand() % 3);
					enemies[num_enemies]->setTileMap(map);
					enemies[num_enemies]->setPlayer(player);
					enemies[num_enemies]->setPlayerPos(player->getCentralPosition());
					++num_enemies;
				}
			}
			else if ((tile == '2') && (num_coins < MAX_COINS)) {
				int coin = rand() % 1000;
				if (coin <= PROB_COINS) {
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
	ostringstream path3;
	path3 << "images/" << currentCharacter << "/infohealth.png";
	texInfoHealth.loadFromFile(path3.str(), TEXTURE_PIXEL_FORMAT_RGBA);
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
		path << "images/" << currentCharacter << "/infolifes" << (i + 1) << ".png";
		texInfoLifes[i].loadFromFile(path.str(), TEXTURE_PIXEL_FORMAT_RGBA);
		texInfoLifes[i].setMagFilter(GL_NEAREST);
		sprInfoLifes[i] = Sprite::createSprite(glm::vec2(32, 32), glm::vec2(1.0f, 1.0f), &texInfoLifes[i], &texProgram);
		sprInfoLifes[i]->setPosition(glm::vec2(SCREEN_X + POS_INFO_X, SCREEN_Y + POS_INFO_Y));
	}

	//Infocooldowns
	for (int i = 0; i < 4; ++i) {
		ostringstream path;
		path << "images/" << currentCharacter << "/infocooldowns" << (i + 1) << ".png";
		t_info_cooldown[i].loadFromFile(path.str(), TEXTURE_PIXEL_FORMAT_RGBA);
		t_info_cooldown[i].setMagFilter(GL_NEAREST);		
		spr_info_cooldown[i] = Sprite::createSprite(glm::vec2(16, 16), glm::vec2(1.0f, 1.0f), &t_info_cooldown[i], &texProgram);
		spr_info_cooldown[i]->setPosition(glm::vec2(SCREEN_X + POS_INFO_X + 126 + 32 * i, SCREEN_Y + POS_INFO_Y + 8));
	}

	//Blocking object (train) and boss
	for (int i = 0; i < spriteMap->getMapSize().x; i++) {
		for (int j = 0; j < spriteMap->getMapSize().y; j++) {
			tile = spriteMap->getMap()[j * spriteMap->getMapSize().x + i];
			glm::vec2 posTile = glm::vec2(SCREEN_X + i * 32, SCREEN_Y + j * 32);
			if (tile == '_') {
				blockObject = new Blocking();
				blockObject->init(texProgram, posTile);
				blockObject->setPosition(posTile);// -glm::vec2(0.0f, 608.0f));
			}
			else if (tile == '`') {
				boss = new Boss();
				boss->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, posTile);
				boss->setTileMap(map);
				boss->setPlayer(player);
				boss->setPlayerPos(player->getCentralPosition());
			}
		}
	}

	//Text
	if (!textScore.init("fonts/ScienceFair.ttf"))
		if (!textScore.init("fonts/OpenSans.ttf"))
			if (!textScore.init("fonts/DroidSerif.ttf"))
				cout << "Could not load font!" << endl;
	score = 0;
	active = true;
	currentTime = 0.0f;
	level_complete = false;

	glm::vec2 pos_enemies[MAX_ENEMIES + 1];
	for (int i = 0; i < MAX_ENEMIES + 1; ++i) pos_enemies[i] = glm::vec2(-1, -1);
	pos_anteriors = pos_enemies;
}

void Level::update(int deltaTime) {
	if (active) {
		currentTime += deltaTime;
		player->update(currentTime, deltaTime, pos_anteriors, MAX_ENEMIES + 1);
		if (active) {
			glm::vec2 pos_enemies[MAX_ENEMIES + 1];
			for (int i = 0; i < MAX_ENEMIES+1; ++i) pos_enemies[i] = glm::vec2(-1,-1);
			if (boss != NULL) {
				boss->setPlayerPos(player->getCentralPosition());
				boss->update(deltaTime, pos_enemies, MAX_ENEMIES+1);
			}
			for (int i = 0; i < num_enemies; ++i) {
				if (enemies[i] != NULL) {
					enemies[i]->setPlayerPos(player->getCentralPosition());
					enemies[i]->update(deltaTime, pos_enemies, MAX_ENEMIES+1);
				}
			}
			pos_anteriors = pos_enemies;
			for (int i = 0; i < num_coins; ++i) {
				if (coins[i] != NULL) {
					coins[i]->update(deltaTime);
				}
			}
			if (blockObject != NULL) {
				blockObject->setPlayerPos(player->getCentralPosition());
				blockObject->update(deltaTime);
			}
			updateInfoHealth(player->getHealth());
		    updatePlayerAttack(player->getDamageDone());
			updateEnemiesAlive();
		}
	}
}

void Level::render(ShaderProgram &texProgram) {
	if (active) {
		//cout << "Score I: " << score << endl;
		skySprite->setPosition(glm::vec2(POS_SKY_X * 32, POS_SKY_Y * 32));
		skySprite->render();
		skySprite->setPosition(glm::vec2(POS_SKY_X * 32 + 1024, POS_SKY_Y * 32));
		skySprite->render();
		skySprite->setPosition(glm::vec2(POS_SKY_X * 32 + 2048, POS_SKY_Y * 32));
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
				else if (tile >= '7' && tile <= ':') {
					int tileAux = tile - int('1');
					glm::vec2 posTile = glm::vec2(SCREEN_X + i * 32, SCREEN_Y + j * 32);
					backSprites[tileAux]->setPosition(posTile);
					backSprites[tileAux]->render();
				}
			}
		}
		for (int i = 0; i < num_coins; ++i) {
			if (coins[i] != NULL) {
				float distance = sqrt(pow(coins[i]->getPosition().x - player->getCentralPosition().x, 2) + pow(coins[i]->getPosition().y - player->getCentralPosition().y, 2));
				if (distance <= 32) {
					coins[i] = NULL;
					score += 10;
				}
				else {
					coins[i]->render();
				}
			}
		}
		if (boss != NULL) boss->render();
		/*for (int i = 0; i < num_enemies; ++i) {
			if (enemies[i] != NULL) enemies[i]->render();
		}*/
		if (blockObject != NULL) {
			blockObject->render();
		}
		glm::vec2 playerPos = player->getBottomPosition();
		int playerPosX = (playerPos.x / 32.0f);
		int playerPosY = ((playerPos.y + 6.0f) / 32.0f);
		glm::ivec2 enemiesPos[MAX_ENEMIES];
		for (int i = 0; i < num_enemies; ++i) {
			if (enemies[i] != NULL) {
				enemiesPos[i] = glm::ivec2(enemies[i]->getBottomPosition().x / 32.0f, (enemies[i]->getBottomPosition().y + 6.0f) / 32.0f);
			}
		}

		for (int j = 0; j < spriteMap->getMapSize().y; j++) {
			for (int i = 0; i < spriteMap->getMapSize().x; i++) {
				tile = spriteMap->getMap()[j * spriteMap->getMapSize().x + i];
				glm::vec2 posTile = glm::vec2(SCREEN_X + i * 32, SCREEN_Y + j * 32);
				if (0 == i && playerPosY == j) {
					player->render();
				}
				if (0 == i) {
					for (int k = 0; k < num_enemies; ++k) {
						if (enemies[k] != NULL && enemiesPos[k].y == j) enemies[k]->render();
					}
				}
				if (tile >= '1' && tile <= ':') {
					int tileAux = tile - int('1');
					sprWall[tileAux]->setBottomPosition(posTile);
					sprWall[tileAux]->render();
				}
				else if (tile >= 'a' && tile <= 'h') {
					int tileAux = tile - int('a');
					sprObject[tileAux]->setBottomPosition(posTile);
					sprObject[tileAux]->render();
				}
				else if (tile >= 'A' && tile <= 'E') {
					int tileAux = tile - int('A');
					sprBuildings[tileAux]->setBottomPosition(posTile);
					sprBuildings[tileAux]->render();
				}
			}
		}
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

		float posAux = (getPlayerPos().x - SCREEN_WIDTH / 2);
		if (posAux < 0.0f) {
			posAux = 0.0f;
		}
		for(int i = 0; i < 4; ++i) {
			if (player->activeCooldownI(i)) {
				spr_info_cooldown[i]->setPosition(glm::vec2(posAux + POS_INFO_X + 126 + 32 * i, POS_INFO_Y + 8));
				spr_info_cooldown[i]->render();
			}
		}

		ostringstream scoreText;
		scoreText << "Score: " << score;
		textScore.render(scoreText.str(), glm::vec2(glutGet(GLUT_WINDOW_WIDTH) * 0.0775f + 1.0f, glutGet(GLUT_WINDOW_HEIGHT) * 0.88f) + 1.0f, float(glutGet(GLUT_WINDOW_WIDTH)) / 80.f, glm::vec4(0.14453125, 0.15625, 0.15234375, 1));
		textScore.render(scoreText.str(), glm::vec2(glutGet(GLUT_WINDOW_WIDTH) * 0.0775f, glutGet(GLUT_WINDOW_HEIGHT) * 0.88f), float(glutGet(GLUT_WINDOW_WIDTH)) / 80.f, glm::vec4(0.91015625, 0.65625, 0.375, 1));
		
		ostringstream timeText;
		long milli = currentTime;
		long min = milli / 60000;
		milli = milli - 60000 * min;
		long sec = milli / 1000;
		milli = milli - 1000 * sec;
		timeText << "Time: " << min << "' " << sec << "''";
		textScore.render(timeText.str(), glm::vec2(glutGet(GLUT_WINDOW_WIDTH) * 0.0775f + 1.0f, glutGet(GLUT_WINDOW_HEIGHT) * 0.9425f) + 1.0f, float(glutGet(GLUT_WINDOW_WIDTH)) / 80.f, glm::vec4(0.14453125, 0.15625, 0.15234375, 1));
		textScore.render(timeText.str(), glm::vec2(glutGet(GLUT_WINDOW_WIDTH) * 0.0775f, glutGet(GLUT_WINDOW_HEIGHT) * 0.9425f), float(glutGet(GLUT_WINDOW_WIDTH)) / 80.f, glm::vec4(0.91015625, 0.65625, 0.375, 1));
	}
}

glm::vec2 Level::getPlayerPos() {
	return player->getCentralPosition();
}

void Level::setPlayerPos(glm::vec2 positionAux) {
	player->setPosition(positionAux);
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
	float x_player = player->getCentralPosition().x;
	float y_player = player->getCentralPosition().y;
	for (int i = 0; i < num_enemies; ++i) {
		if (enemies[i] != NULL) {
			float x_enemy = enemies[i]->getCentralPosition().x;
			float y_enemy = enemies[i]->getCentralPosition().y;
			float dif_x = abs(x_player - x_enemy);
			float dif_y = abs(y_player - y_enemy);
			if (!right && x_enemy >= x_player && dif_x <= 75 && dif_y <= 88) {
				enemies[i]->takeDamage(damage);
			}
			else if (right && x_enemy <= x_player && dif_x <= 75 && dif_y <= 88) {
				enemies[i]->takeDamage(damage);
			}
		}
	}
	if (boss != NULL) {
		float x_boss = boss->getCentralPosition().x;
		float y_boss = boss->getCentralPosition().y;
		float dif_x = abs(x_player - x_boss);
		float dif_y = abs(x_player - y_boss);
		if (!right && x_boss >= x_player && dif_x <= 85 && dif_y <= 98) {
			boss->takeDamage(damage);
		}
		else if (right && x_boss < x_player && dif_x <= 85 && dif_y <= 98) {
			boss->takeDamage(damage);
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
	if (boss != NULL) boss->restart();
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
	textScore.destroy();
	if (!textScore.init("fonts/ScienceFair.ttf"))
		if (!textScore.init("fonts/OpenSans.ttf"))
			if (!textScore.init("fonts/DroidSerif.ttf"))
				cout << "Could not load font!" << endl;

	//Blocking object
	int tile;
	if (blockObject != NULL) {
		blockObject->restart();
	}

	Game::instance().setScore(Game::instance().getScore() + score);

	score = 0;
	active = true;
	currentTime = 0.0f;
}

void Level::updateEnemiesAlive() {
	for (int i = 0; i < num_enemies; ++i) {
		if (enemies[i] != NULL && enemies[i]->getHealth() < 1) {
			score += enemies[i]->getScore(); //Fer un get de enemic que retorni una puntuacio X en funcio del enemic
			enemies[i] = NULL;
		}
	}
	if (boss != NULL && boss->getFase() < 1) {
		score += boss->getScore();
		boss = NULL;
		level_complete = true;
	}
}

int Level::getScore() {
	return score;
}

void Level::setCharacter(int characterAux) {
	currentCharacter = characterAux;
}

int Level::getCharacter() {
	return currentCharacter;
}

bool Level::complete() {
	return level_complete;
}