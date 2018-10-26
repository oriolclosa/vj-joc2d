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
	
}

void Player::update(int deltaTime){
	sprite->update(deltaTime);
	if(Game::instance().getSpecialKey(GLUT_KEY_LEFT)){
		posPlayer.x -= WALK_SPEED;
		if(map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32), false)){
			posPlayer.x += WALK_SPEED;
		}
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT)){
		posPlayer.x += WALK_SPEED;
		if(map->collisionMoveRight(posPlayer, glm::ivec2(32, 32), false)){
			posPlayer.x -= WALK_SPEED;
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_UP)){
		posPlayer.y -= WALK_SPEED;
		if (map->collisionMoveUp(posPlayer, glm::ivec2(32, 32), false)){
			posPlayer.y += WALK_SPEED;
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
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




