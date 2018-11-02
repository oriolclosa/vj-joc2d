#include <cmath>
#include <iostream>
#include <sstream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <cstdlib> 
#include "Game.h"
#include "Level.h"
#include "Boss.h"


#define WALK_SPEED 2
#define DETECT_DISTANCE 350

#define PLAYER_DAMAGE 10

#define HEALTH 100
#define FASE 3

#define CENTRAL_X 40
#define CENTRAL_Y 48
#define INNER_X 36  // NPI
#define INNER_Y 78  // NPI
#define CORNER_X 45 // NPI
#define CORNER_Y 47 // NPI


enum BossAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, ATTACK_1, ATTACK_2
};

void Boss::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, glm::vec2 pos) {
	type = Game::instance().getCurrentLevel();

	focus = false;

	iniPosition = pos;
	posPlayer = pos;

	health = HEALTH;
	fase = FASE;

	// Sprites del enemic
	ostringstream path;
	path << "images/0/boss" << type << ".png";
	spritesheet.loadFromFile(path.str(), TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(96, 96), glm::vec2(0.25f, 0.25f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(6);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.75f, 0.75f));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.5f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.25f, 0.5f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.5f, 0.5f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.75f, 0.5f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.0f, 0.75f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25f, 0.75f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5f, 0.75f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.75f, 0.75f));

	sprite->setAnimationSpeed(ATTACK_1, 8);
	sprite->addKeyframe(ATTACK_1, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(ATTACK_2, 8);
	sprite->addKeyframe(ATTACK_2, glm::vec2(0.f, 0.25f));

	sprite->changeAnimation(STAND_LEFT);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x - tileMapDispl.x ), float(tileMapDispl.y - tileMapDispl.y)));
}

void Boss::update(int deltaTime, glm::vec2 *pos_enemies, int n) {
	sprite->update(deltaTime);
	float distance = sqrt(pow(playerPos.x - getCentralPosition().x, 2) + pow(playerPos.y - getCentralPosition().y, 2));
	bool xSpace = playerPos.x > posPlayer.x || playerPos.x + 32 < posPlayer.x;
	bool ySpace = playerPos.y > posPlayer.y || playerPos.y + 64 < posPlayer.y;
	if (distance < DETECT_DISTANCE && (xSpace || ySpace) && distance > 56) {
		focus = true;
		float incX = 0.0f, incY = 0.0f;
		if (playerPos.x > posPlayer.x) {
			if(sprite->animation() != MOVE_RIGHT) sprite->changeAnimation(MOVE_RIGHT);
			if (playerPos.y != posPlayer.y) {
				incX = WALK_SPEED/2;
			}
			else {
				incX = WALK_SPEED;
			}
		}
		else if (playerPos.x < posPlayer.x) {
			if(sprite->animation() != MOVE_LEFT) sprite->changeAnimation(MOVE_LEFT);
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
		if (incX < 0 && map->collisionMoveLeft(glm::vec2(posPlayer.x + incX, posPlayer.y + incY), glm::ivec2(64, 96), true)) {
			if(sprite->animation() != STAND_LEFT) sprite->changeAnimation(STAND_LEFT);
			incX = 0;
		}
		else if (incX > 0 && map->collisionMoveRight(glm::vec2(posPlayer.x + incX, posPlayer.y + incY), glm::ivec2(64, 96), true)) {
			if(sprite->animation() != STAND_RIGHT) sprite->changeAnimation(STAND_RIGHT);
			incX = 0;
		}
		if (incY < 0 && map->collisionMoveDown(glm::vec2(posPlayer.x + incX, posPlayer.y + incY), glm::ivec2(64, 96), true)) {
			incY = 0;
		}
		else if (incY > 0 && map->collisionMoveUp(glm::vec2(posPlayer.x + incX, posPlayer.y + incY), glm::ivec2(64, 96), true)) {
			incY = 0;
		}
		int i = 0;
		while (i < n && pos_enemies[i] != glm::vec2(-1,-1)) {
			if (abs(pos_enemies[i].x - getCentralPosition().x + incX) < 42) incX = 0;
			if (abs(pos_enemies[i].y - getCentralPosition().y + incY) < 62) incY = 0;
			++i;
		}
		posPlayer.x += int(incX);
		posPlayer.y += int(incY);
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	}
	else if (distance <= 66) {
		if(fase == 3) {
			sprite->changeAnimation(ATTACK_1);
			attackPlayer(PLAYER_DAMAGE);
		}
		else if (fase == 2) {
			sprite->changeAnimation(ATTACK_2);
			attackPlayer(PLAYER_DAMAGE * 0.2);
		}
		else {
			if (rand() % 2 == 0) {
				sprite->changeAnimation(ATTACK_1);
				attackPlayer(PLAYER_DAMAGE * 0.2);
			}
			else
				attackPlayer(PLAYER_DAMAGE * 0.6);
		}
	}
	else {
		if (sprite->animation() == MOVE_RIGHT || sprite->animation() == STAND_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
		else sprite->changeAnimation(STAND_LEFT);
	}
	int i = 0;
	while (pos_enemies[i] != glm::vec2(-1,-1)) ++i;
	pos_enemies[i] = glm::vec2(getCentralPosition().x,getCentralPosition().y);
}

void Boss::attackPlayer(float damage) {
	if (abs(playerPos.x - getCentralPosition().x) <= 132)
		if (abs(playerPos.y - getCentralPosition().y) <= 56)
			player->takeDamage(damage);
}

void Boss::takeDamage(float damage) {
	sprite->setHit(true);
	health -= damage;
	if (health < 1) {
		--fase;
		restart();
	}
}

int Boss::getScore() {
	return 2100;
}

int Boss::getFase() {
	return fase;
}

bool Boss::getFocus() { // Fer barra de vida?
	return focus;
}

void Boss::restart() {
	health = HEALTH - (3 - fase) * 10.f;
	sprite->setHit(false);
	posPlayer = iniPosition;
	sprite->setPosition(posPlayer);
}
