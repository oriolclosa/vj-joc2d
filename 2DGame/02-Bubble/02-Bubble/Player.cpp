#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4

#define WALK_SPEED 5

enum PlayerAnimations{
	WALK, ATTACK_1, ATTACK_2, ATTACK_3
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram){
	spritesheet.loadFromFile("images/0/character.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(128, 176), glm::vec2(1.0f / 56.0f, 1.0f / 4.0f), &spritesheet, &shaderProgram);

	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(WALK, 24);
	for (int i = 0; i < 12; ++i) {
		sprite->addKeyframe(WALK, glm::vec2(float(i) / 56.0f, 0.0f));
	}

	sprite->setAnimationSpeed(ATTACK_1, 24);
	for (int i = 0; i < 16; ++i) {
		sprite->addKeyframe(ATTACK_1, glm::vec2(float(i) / 56.0f, 1.0f / 4.0f));
	}

	sprite->setAnimationSpeed(ATTACK_2, 24);
	for (int i = 0; i < 25; ++i) {
		sprite->addKeyframe(ATTACK_2, glm::vec2(float(i) / 56.0f, 2.0f / 4.0f));
	}

	sprite->setAnimationSpeed(ATTACK_3, 24);
	for (int i = 0; i < 56; ++i) {
		sprite->addKeyframe(ATTACK_3, glm::vec2(float(i) / 56.0f, 3.0f / 4.0f));
	}

	sprite->changeAnimation(WALK);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	lifes = 3;
	health = 100.f;
	right = false;
	coolDownA1 = coolDownA2 = coolDownA3 = 0;
	damageDone = 0;
	coolDownRec1 = coolDownRec2 = 0;
	coolDownDamage = 0;
}

void Player::update(int deltaTime){
	sprite->update(deltaTime);
	if (coolDownDamage > 0) --coolDownDamage;
	if (health < 100 && coolDownRec1 == 0) {
		if (coolDownRec2 > 0) --coolDownRec2;
		if (coolDownRec2 == 0) {
			health += 1;
			coolDownRec2 = 100;
		}
	}
	if (coolDownRec1 > 0) --coolDownRec1;
	damageDone = 0;
	if (coolDownA1 > 0) --coolDownA1;
	if (coolDownA2 > 0) --coolDownA2;
	if (coolDownA3 > 0) --coolDownA3;
	if (health <= 0) death();
	if (Game::instance().getKey(101) && coolDownA1 == 0) { // e, Attack 1
		sprite->changeAnimation(ATTACK_1);
		doDamage(10);
		coolDownA1 = 90;
	}
	else if (Game::instance().getKey(102) && coolDownA2 == 0) { // f, Attack 2
		sprite->changeAnimation(ATTACK_2);
		doDamage(20);
		coolDownA2 = 165;
	}
	else if (Game::instance().getKey(32) && coolDownA3 == 0) { // SPACE, Attack 3
		sprite->changeAnimation(ATTACK_3);
		doDamage(40);
		coolDownA3 = 420;
	}
	else if(Game::instance().getKey(97)){ // a
		posPlayer.x -= WALK_SPEED;
		right = true;
		if(map->collisionMoveLeft(getCornerPosition(), getInnerSize(), false)){
			posPlayer.x += WALK_SPEED;
		}
	}
	else if(Game::instance().getKey(100)){ // d
		posPlayer.x += WALK_SPEED;
		right = false;
		if(map->collisionMoveRight(getCornerPosition(), getInnerSize(), false)){
			posPlayer.x -= WALK_SPEED;
		}
	}
	else if (Game::instance().getKey(119)){ // w
		posPlayer.y -= WALK_SPEED;
		if (map->collisionMoveUp(getCornerPosition(), getInnerSize(), false)){
			posPlayer.y += WALK_SPEED;
		}
	}
	else if (Game::instance().getKey(115)) { // s
		posPlayer.y += WALK_SPEED;
		if (map->collisionMoveDown(getCornerPosition(), getInnerSize(), false)) {
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
	if (coolDownDamage == 0) {
		health -= damage;
		coolDownRec1 = 600;
		coolDownRec2 = 0;
		coolDownDamage = 120;
	}
}

void Player::death() {
	health = 100;
	--lifes;
	if (lifes < 1) {
		Game::instance().setRenderScene(5);
		Game::instance().getScene().updateLevel(-1);
		//cout << "Score: " << Game::instance().getScore() << endl;
	}
	else {
		Game::instance().getScene().restartLevel();
	}
}

void Player::doDamage(float damage) {
	damageDone = damage;
}

float Player::getHealth() {
	return health;
}

int Player::getLifes() {
	return lifes;
}

float Player::getDamageDone() {
	return damageDone;
}

bool Player::getDirection() {
	return right;
}

glm::vec2 Player::getCentralPosition() {
	return posPlayer + glm::ivec2(64, 88);
}

glm::vec2 Player::getBottomPosition() {
	return posPlayer + glm::ivec2(64, 176);
}

glm::vec2 Player::getCornerPosition() {
	return posPlayer + glm::ivec2(45, 57);
}

glm::vec2 Player::getInnerSize() {
	return glm::ivec2(36, 78);
}