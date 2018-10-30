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

#define HEALTH 100
#define LIFES 3

#define DAMAGE_ATTACK_1 30
#define DAMAGE_ATTACK_2 40
#define DAMAGE_ATTACK_3 70

#define COOLDOWN_ATTACK_1 45
#define COOLDOWN_ATTACK_2 85 
#define COOLDOWN_ATTACK_3 210

#define COOLDOWN_START_RECUPERATION 600
#define COOLDOWN_BETWEEN_RECUPERATIONS 100

#define SAFE_TIME_BETWEEN_HITS 30

enum PlayerAnimations{
	WALK, ATTACK_1, ATTACK_2, ATTACK_3
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram){
	spritesheet.loadFromFile("images/0/character.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(128, 176), glm::vec2(1.0f / 56.0f, 1.0f / 4.0f), &spritesheet, &shaderProgram);
	sprite->setSize(glm::vec2(128, 76));

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

	freez = 0;

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	lifes = LIFES;
	health = HEALTH;
	right = false;
	sprite->lookRight(right);
	coolDownA1 = coolDownA2 = coolDownA3 = 0;
	damageDone = 0;
	coolDownRec1 = coolDownRec2 = 0;
	coolDownDamage = 0;
}

void Player::update(float totalTime, int deltaTime){
	sprite->update(totalTime, deltaTime);
	if (coolDownDamage > 0) --coolDownDamage;
	if (health < HEALTH && coolDownRec1 == 0) {
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
	if (freez > 0) --freez;
	else if ((Game::instance().getKey(101) || Game::instance().getKey(69)) && coolDownA1 == 0) { // e E, Attack 1
		sprite->changeAnimation(ATTACK_1);
		sprite->resetToAnimation(totalTime, 1000.0f*(16.0f / 24.0f), WALK);
		doDamage(DAMAGE_ATTACK_1);
		coolDownA1 = COOLDOWN_ATTACK_1;
		freez = 36;
	}
	else if ((Game::instance().getKey(102) || Game::instance().getKey(70)) && coolDownA2 == 0) { // f F, Attack 2
		sprite->changeAnimation(ATTACK_2);
		sprite->resetToAnimation(totalTime, 1000.0f*(25.0f / 24.0f), WALK);
		doDamage(DAMAGE_ATTACK_2);
		coolDownA2 = COOLDOWN_ATTACK_2;
		freez = 58;
	}
	else if (Game::instance().getKey(32) && coolDownA3 == 0) { // SPACE, Attack 3
		sprite->changeAnimation(ATTACK_3);
		sprite->resetToAnimation(totalTime, 1000.0f*(56.0f / 24.0f), WALK);
		doDamage(DAMAGE_ATTACK_3);
		coolDownA3 = COOLDOWN_ATTACK_3;
		freez = 150;
	}
	else if(Game::instance().getKey(97) || Game::instance().getKey(65)){ // a A
		posPlayer.x -= WALK_SPEED;
		right = true;
		sprite->lookRight(right);
		if(map->collisionMoveLeft(getCornerPosition(), getInnerSize(), false)){
			posPlayer.x += WALK_SPEED;
		}
	}
	else if(Game::instance().getKey(100) || Game::instance().getKey(68)){ // d D
		posPlayer.x += WALK_SPEED;
		right = false;
		sprite->lookRight(right);
		if(map->collisionMoveRight(getCornerPosition(), getInnerSize(), false)){
			posPlayer.x -= WALK_SPEED;
		}
	}
	else if (Game::instance().getKey(119) || Game::instance().getKey(87)){ // w W
		--health;
		posPlayer.y -= WALK_SPEED;
		if (map->collisionMoveUp(getCornerPosition(), getInnerSize(), false)){
			posPlayer.y += WALK_SPEED;
		}
	}
	else if (Game::instance().getKey(115) || Game::instance().getKey(83)) { // s S
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
		coolDownRec1 = COOLDOWN_START_RECUPERATION;
		coolDownRec2 = 0;
		coolDownDamage = SAFE_TIME_BETWEEN_HITS;
	}
}

void Player::death() {
	health = HEALTH;
	--lifes;
	if (lifes < 1) {
		Game::instance().setRenderScene(5);
		Game::instance().getScene().updateLevel(-1);
		//cout << "Score: " << Game::instance().getScore() << endl;
	}
	else {
		sprite->changeAnimation(WALK);
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

bool Player::activeCooldownI(int i) {
	switch(i) {
		case 0:
			return coolDownRec1 > 0;
			break;
		case 1:
			return coolDownA1 > 0;
			break;
		case 2:
			return coolDownA2 > 0;
		case 3:
			return coolDownA3 > 0;
	}
}