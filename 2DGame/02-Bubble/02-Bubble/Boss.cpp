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

#define CENTRAL_X 100
#define CENTRAL_Y 100
#define INNER_X 100  // NPI
#define INNER_Y 100  // NPI
#define CORNER_X 62 // NPI
#define CORNER_Y 62 // NPI


enum BossAnims
{
	STAND, WALK, ATTACK1, ATTACK2
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
	path << "images/" << Game::instance().getSelectedCharacter()+1 << "/boss.png";
	spritesheet.loadFromFile(path.str(), TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(200, 200), glm::vec2(1.0f/14.0f, 1.0f/3.0f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(STAND, 1);
	sprite->addKeyframe(STAND, glm::vec2(0.0f, 0.0f));

	sprite->setAnimationSpeed(WALK, 12);
	for (int i = 0; i < 10; ++i) {
		sprite->addKeyframe(WALK, glm::vec2((float(i) / 14.0f), 0.0f));
	}

	sprite->setAnimationSpeed(ATTACK1, 12);
	for (int i = 0; i < 13; ++i) {
		sprite->addKeyframe(ATTACK1, glm::vec2((float(i) / 14.0f), 1.0f/3.0f));
	}

	sprite->setAnimationSpeed(ATTACK2, 24);
	for (int i = 0; i < 14; ++i) {
		sprite->addKeyframe(ATTACK2, glm::vec2((float(i) / 14.0f), 2.0f / 3.0f));
	}

	sprite->changeAnimation(STAND);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Boss::update(int deltaTime, glm::vec2 *pos_enemies, int n) {
	sprite->update(deltaTime);
	float distance = sqrt(pow(playerPos.x - getCentralPosition().x, 2) + pow(playerPos.y - getCentralPosition().y, 2));
	//bool xSpace = playerPos.x > posPlayer.x || playerPos.x + 32 < posPlayer.x;
	//bool ySpace = playerPos.y > posPlayer.y || playerPos.y + 64 < posPlayer.y;
	cout << "POS: " << posPlayer.x << ' ' << posPlayer.y << ' ' << getCentralPosition().x << ' ' << getCentralPosition().y << endl;
	if (distance < DETECT_DISTANCE &&  distance > 100) {
		cout << "YES" << endl;
		focus = true;
		float incX = 0.0f, incY = 0.0f;
		if (playerPos.x > posPlayer.x) {
			sprite->lookRight(false);
			if (sprite->animation() != WALK) {
				sprite->changeAnimation(WALK);
			}
			if (playerPos.y != posPlayer.y) {
				incX = WALK_SPEED/2;
			}
			else {
				incX = WALK_SPEED;
			}
		}
		else if (playerPos.x < posPlayer.x) {
			sprite->lookRight(true);
			if (sprite->animation() != WALK) {
				sprite->changeAnimation(WALK);
			}
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
			if (abs(pos_enemies[i].x - getCentralPosition().x + incX) < 42 && abs(pos_enemies[i].y - getCentralPosition().y + incY) < 62) {
				incX = 0;
				incY = 0;
			}
			++i;
		}
		posPlayer.x += int(incX);
		posPlayer.y += int(incY);
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	}
	else if (distance <= 100) {
		cout << "NO" << endl;
		if(fase == 3) {
			sprite->changeAnimation(ATTACK1);
			attackPlayer(PLAYER_DAMAGE);
		}
		else if (fase == 2) {
			sprite->changeAnimation(ATTACK2);
			attackPlayer(PLAYER_DAMAGE * 0.2);
		}
		else {
			if (rand() % 2 == 0) {
				sprite->changeAnimation(ATTACK1);
				attackPlayer(PLAYER_DAMAGE * 0.2);
			}
			else
				attackPlayer(PLAYER_DAMAGE * 0.6);
		}
	}
	else {
		sprite->changeAnimation(STAND);
		cout << "XD" << endl;
	}
	int i = 0;
	while (pos_enemies[i] != glm::vec2(-1,-1)) ++i;
	pos_enemies[i] = glm::vec2(getCentralPosition().x,getCentralPosition().y);
}

void Boss::attackPlayer(float damage) {
	if (abs(playerPos.x - getCentralPosition().x) <= 240)
		if (abs(playerPos.y - getCentralPosition().y) <= 165)
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

glm::vec2 Boss::getCentralPosition() {
	return posPlayer + glm::ivec2(CENTRAL_X, CENTRAL_Y);
}

glm::vec2 Boss::getInnerSize() {
	return glm::ivec2(INNER_X, INNER_Y);
}

glm::vec2 Boss::getCornerPosition() {
	return posPlayer + glm::ivec2(CORNER_X, CORNER_Y);
}

glm::vec2 Boss::getBottomPosition() {
	return posPlayer + glm::ivec2(100, 200);
}