#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Enemy.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4

#define WALK_SPEED 2
#define DETECT_DISTANCE 250


void Enemy::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram){
	spritesheet.loadFromFile("images/margaret/wall.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Enemy::update(int deltaTime){
	sprite->update(deltaTime);
	float distance = sqrt(pow(playerPos.x - posPlayer.x, 2) + pow(playerPos.y - posPlayer.y, 2));
	if (distance < DETECT_DISTANCE) {
		float incX = 0.0f, incY = 0.0f;
		if (playerPos.x > posPlayer.x) {
			if (playerPos.y != posPlayer.y) {
				incX = WALK_SPEED/2;
			}
			else {
				incX = WALK_SPEED;
			}
		}
		else if (playerPos.x < posPlayer.x) {
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
		if (incX < 0 && map->collisionMoveLeft(glm::vec2(posPlayer.x + incX, posPlayer.y + incY), glm::ivec2(32, 32))) {
			incX = 0;
		}
		else if (incX > 0 && map->collisionMoveRight(glm::vec2(posPlayer.x + incX, posPlayer.y + incY), glm::ivec2(32, 32))) {
			incX = 0;
		}
		if (incY < 0 && map->collisionMoveDown(glm::vec2(posPlayer.x + incX, posPlayer.y + incY), glm::ivec2(32, 32))) {
			incY = 0;
		}
		else if (incY > 0 && map->collisionMoveUp(glm::vec2(posPlayer.x + incX, posPlayer.y + incY), glm::ivec2(32, 32))) {
			incY = 0;
		}
		posPlayer.x += incX;
		posPlayer.y += incY;
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	}
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



