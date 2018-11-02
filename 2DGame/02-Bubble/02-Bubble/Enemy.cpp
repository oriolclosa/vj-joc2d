#include <cmath>
#include <iostream>
#include <sstream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <cstdlib> 
#include "Enemy.h"
#include "Game.h"
#include "Level.h"


#define WALK_SPEED 3
#define DETECT_DISTANCE 350

#define PLAYER_DAMAGE 4

#define HEALTH 100

#define CENTRAL_X 64
#define CENTRAL_Y 88
#define INNER_X 36
#define INNER_Y 78
#define CORNER_X 45
#define CORNER_Y 47


enum EnemyAnims{
	STAND, WALK, ATTACK
};

void Enemy::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, glm::vec2 pos, int enemyType) {
	type = enemyType;

	iniPosition = pos;
	posPlayer = pos;

	// Vida diferent per tipus enemic
	health = HEALTH;
	if (type == 0) health *= 0.5f;
	else if (type == 2)  health *= 0.5f;

	// Sprites del enemic
	ostringstream path;
    path << "images/" << Game::instance().getSelectedCharacter() << "/enemy" << type << ".png";
	spritesheet.loadFromFile(path.str(), TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(138, 171), glm::vec2((1.0f / 8.0f), 0.5f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2); //WTF?

	sprite->setAnimationSpeed(STAND, 1);
	sprite->addKeyframe(STAND, glm::vec2(0.0f, 0.0f));

	sprite->setAnimationSpeed(WALK, 8);
	for (int i = 0; i < 7; ++i) {
		sprite->addKeyframe(WALK, glm::vec2((float(i) / 8.0f), 0.0f));
	}

	sprite->setAnimationSpeed(ATTACK, 8);
	int framesAttack[3] = {8, 6, 7};
	for (int i = 0; i < framesAttack[type]; ++i) {
		sprite->addKeyframe(WALK, glm::vec2((float(i) / 8.0f), 0.5f));
	}

	sprite->changeAnimation(STAND);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Enemy::update(int deltaTime, glm::vec2 *pos_enemies, int n){
	sprite->update(deltaTime);
	float distance = sqrt(pow(playerPos.x - getCentralPosition().x, 2) + pow(playerPos.y - getCentralPosition().y, 2));
	bool xSpace = playerPos.x > posPlayer.x || playerPos.x + 32 < posPlayer.x;
	bool ySpace = playerPos.y > posPlayer.y || playerPos.y + 64 < posPlayer.y;
	if (distance < DETECT_DISTANCE && (xSpace || ySpace) && distance > 46) {
		float incX = 0.0f, incY = 0.0f;
		if (playerPos.x > getCentralPosition().x) {
			sprite->lookRight(false);
			if (sprite->animation() != WALK) {
				sprite->changeAnimation(WALK);
			}
			if (playerPos.y != posPlayer.y) incX = WALK_SPEED/2;
			else incX = WALK_SPEED; 
		}
		else if (playerPos.x < getCentralPosition().x) {
			sprite->lookRight(true);
			if (sprite->animation() != WALK) {
				sprite->changeAnimation(WALK);
			}
			if (playerPos.y != posPlayer.y) incX = -WALK_SPEED / 2;
			else incX = -WALK_SPEED;
		}
		if (playerPos.y > getCentralPosition().y) {
			if (playerPos.x != posPlayer.x) incY = WALK_SPEED / 2;
			else incY = WALK_SPEED;
		}
		else if (playerPos.y < getCentralPosition().y) {
			if (playerPos.x != posPlayer.x) incY = -WALK_SPEED / 2;
			else incY = -WALK_SPEED;
		}
		if (incX < 0 && map->collisionMoveLeft(getCornerPosition() + glm::vec2(incX, incY), getInnerSize(), true)) {
			sprite->changeAnimation(STAND);
			incX = 0;
		}
		else if (incX > 0 && map->collisionMoveRight(getCornerPosition() + glm::vec2(incX, incY), getInnerSize(), true)) {
			sprite->changeAnimation(STAND);
			incX = 0;
		}
		if (incY < 0 && map->collisionMoveDown(getCornerPosition() + glm::vec2(incX, incY), getInnerSize(), true)) {
			incY = 0;
		}
		else if (incY > 0 && map->collisionMoveUp(getCornerPosition() + glm::vec2(incX, incY), getInnerSize(), true)) {
			incY = 0;
		}
		int i = 0;
		while (i < n && pos_enemies[i] != glm::vec2(-1,-1)) {
			if (abs(pos_enemies[i].x - getCentralPosition().x + incX) < 22) incX = 0;
			if (abs(pos_enemies[i].y - getCentralPosition().y + incY) < 32) incY = 0;
			++i;
		}
		posPlayer.x += incX;
		posPlayer.y += incY;
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	}
	else if (distance <= 46) {
		if ((sprite->animation() == STAND || sprite->animation() == WALK) && sprite->animation() != ATTACK) {
			sprite->changeAnimation(ATTACK);
		}
		attackPlayer(PLAYER_DAMAGE * (3 - type));
	}
	else sprite->changeAnimation(STAND);
	int i = 0;
	while (pos_enemies[i] != glm::vec2(-1,-1)) ++i;
	pos_enemies[i] = glm::vec2(getCentralPosition().x,getCentralPosition().y);
}

void Enemy::render(){
	sprite->render();
}

void Enemy::setTileMap(TileMap *tileMap){
	map = tileMap;
}

void Enemy::setPosition(const glm::vec2 &pos){
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

glm::vec2 Enemy::getPosition() {
	return posPlayer;
}

void Enemy::setPlayerPos(glm::vec2 &playerPosAux) {
	playerPos = playerPosAux;
}

void Enemy::attackPlayer(float damage) {
	if (abs(playerPos.x - getCentralPosition().x) <= 166)
		if (abs(playerPos.y - getCentralPosition().y) <= 88)
			player->takeDamage(damage);
}

void Enemy::setPlayer(Player *playerAux) {
	player = playerAux;
}

void Enemy::takeDamage(float damage) {
	sprite->setHit(true);
	health -= damage;
}

void Enemy::restart() {
	health = HEALTH;
	if (type == 0) health *= 0.75f;
	else if (type == 2)  health *= 1.25f;
	sprite->setHit(false);
	posPlayer = iniPosition;
	sprite->setPosition(posPlayer);
}

float Enemy::getHealth() {
	return health;
}

int Enemy::getScore() {
	return type * 20;
}

glm::vec2 Enemy::getCentralPosition() {
	return posPlayer + glm::ivec2(CENTRAL_X, CENTRAL_Y);
}

glm::vec2 Enemy::getInnerSize() {
	return glm::ivec2(INNER_X, INNER_Y);
}

glm::vec2 Enemy::getCornerPosition() {
	return posPlayer + glm::ivec2(CORNER_X, CORNER_Y);
}