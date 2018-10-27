#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4

#define WALK_SPEED 3


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram){
	spritesheet.loadFromFile("images/bub.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	lifes = 3;
	health = 100.f;
	right = false;
}

void Player::update(int deltaTime){
	sprite->update(deltaTime);
	if (health <= 0) death();
		if (Game::instance().getKey(32)) { //SPACE
		doDamage(10);
	}
	else if (Game::instance().getKey(101)) { //SPACE
		doDamage(20);
	}
	else if (Game::instance().getKey(102)) { //SPACE
		doDamage(40);
	}
	else if(Game::instance().getKey(97)){ // a
		posPlayer.x -= WALK_SPEED;
		right = true;
		if(map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32), false)){
			posPlayer.x += WALK_SPEED;
		}
	}
	else if(Game::instance().getKey(100)){ // d
		//--health;
		posPlayer.x += WALK_SPEED;
		right = false;
		if(map->collisionMoveRight(posPlayer, glm::ivec2(32, 32), false)){
			posPlayer.x -= WALK_SPEED;
		}
	}
	else if (Game::instance().getKey(119)){ // w
		posPlayer.y -= WALK_SPEED;
		if (map->collisionMoveUp(posPlayer, glm::ivec2(32, 32), false)){
			posPlayer.y += WALK_SPEED;
		}
	}
	else if (Game::instance().getKey(115)) { // s
		posPlayer.y += WALK_SPEED;
		if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), false)) {
			posPlayer.y -= WALK_SPEED;
		}
	}
	
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render(){
	sprite->render();
}

void Player::setTileMap(TileMap *tileMap){
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos){
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

glm::vec2 Player::getPosition() {
	return posPlayer;
}

void Player::takeDamage(float damage) {
	health -= damage;
}

void Player::death() {
	health = 100;
	--lifes;
	if (lifes < 1) {
		Game::instance().setRenderScene(1);
		Game::instance().getScene().updateLevel(-1);
	}
	else {
		Game::instance().getScene().restartLevel();
	}
}

void Player::doDamage(float damage) {
	health -= damage;
}

float Player::getHealth() {
	return health;
}

int Player::getLifes() {
	return lifes;
}
