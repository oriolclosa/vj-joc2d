#include <cmath>
#include <iostream>
#include <sstream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Enemy.h"
#include "Game.h"
#include "Level.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4

#define WALK_SPEED 4
#define DETECT_DISTANCE 350

#define PLAYER_DAMAGE 5

#define HEALTH 100


enum EnemyAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};

void Enemy::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, glm::vec2 pos, int enemyType) {
	type = enemyType;

	tileMapDispl = tileMapPos;
	iniPosition = pos;
	posPlayer = pos;

	// Vida diferent per tipus enemic
	health = HEALTH;
	if (type == 0) health *= 0.5f;
	else if (type == 2)  health *= 0.5f;

	// Sprites del enemic
	ostringstream path;
	path << "images/0/enemy" << type << ".png";
	spritesheet.loadFromFile(path.str(), TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.0f, 1.0f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);
	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));
	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, -1.f));
	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x - tileMapDispl.x ), float(tileMapDispl.y - tileMapDispl.y)));
}

void Enemy::update(int deltaTime){
	sprite->update(deltaTime);
	float distance = sqrt(pow(playerPos.x - posPlayer.x, 2) + pow(playerPos.y + 16 - posPlayer.y, 2));
	bool xSpace = playerPos.x > posPlayer.x || playerPos.x + 32 < posPlayer.x;
	bool ySpace = playerPos.y > posPlayer.y || playerPos.y + 64 < posPlayer.y;
	if (distance < DETECT_DISTANCE && (xSpace || ySpace) && distance > 32) {
		float incX = 0.0f, incY = 0.0f;
		if (playerPos.x > posPlayer.x) {
			sprite->changeAnimation(STAND_LEFT);
			if (playerPos.y != posPlayer.y) {
				incX = WALK_SPEED/2;
			}
			else {
				incX = WALK_SPEED;
			}
		}
		else if (playerPos.x < posPlayer.x) {
			sprite->changeAnimation(STAND_RIGHT);
			if (playerPos.y != posPlayer.y) {
				incX = -WALK_SPEED / 2;
			}
			else {
				incX = -WALK_SPEED;
			}
		}
		if (playerPos.y > posPlayer.y) {
			if (playerPos.x != posPlayer.x) {
				incY = WALK_SPEED / 2;
			}
			else {
			incY = WALK_SPEED;
			}
		}
		else if (playerPos.y < posPlayer.y) {
			if (playerPos.x != posPlayer.x) {
				incY = -WALK_SPEED / 2;
			}
			else {
				incY = -WALK_SPEED;
			}
		}
		if (incX < 0 && map->collisionMoveLeft(glm::vec2(posPlayer.x + incX, posPlayer.y + incY), glm::ivec2(32, 32), true)) {
			incX = 0;
		}
		else if (incX > 0 && map->collisionMoveRight(glm::vec2(posPlayer.x + incX, posPlayer.y + incY), glm::ivec2(32, 32), true)) {
			incX = 0;
		}
		if (incY < 0 && map->collisionMoveDown(glm::vec2(posPlayer.x + incX, posPlayer.y + incY), glm::ivec2(32, 32), true)) {
			incY = 0;
		}
		else if (incY > 0 && map->collisionMoveUp(glm::vec2(posPlayer.x + incX, posPlayer.y + incY), glm::ivec2(32, 32), true)) {
			incY = 0;
		}
		posPlayer.x += incX;
		posPlayer.y += incY;
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	}
	else if (distance <= 32) attackPlayer(PLAYER_DAMAGE);
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
	if (abs(playerPos.x - posPlayer.x) <= 64)
		if (abs(playerPos.y - posPlayer.y) <= 64)
			player->takeDamage(damage);
}

void Enemy::setPlayer(Player *playerAux) {
	player = playerAux;
}

void Enemy::takeDamage(float damage) {
	health -= damage;
}

void Enemy::restart() {
	posPlayer = iniPosition;
	sprite->setPosition(posPlayer);
}

float Enemy::getHealth() {
	return health;
}

int Enemy::getScore() {
	return type * 20;
}