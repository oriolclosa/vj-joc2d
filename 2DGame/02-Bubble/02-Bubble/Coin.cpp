#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Coin.h"
#include "Game.h"
#include "Level.h"


void Coin::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, glm::vec2 pos) {
	spritesheet.loadFromFile("images/margaret/coins.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.0f/6.0f, 1.0f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);
	sprite->setAnimationSpeed(0, 5);
	for (int i = 0; i < 6; ++i) {
		sprite->addKeyframe(0, glm::vec2((float(i) / 6.0f), 1.0f));
	}
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	extraTime = rand() % 10;
	iniPosition = pos;
	posPlayer = pos;
}

void Coin::update(int deltaTime) {
	sprite->update(deltaTime + extraTime);
}

void Coin::render() {
	sprite->render();
}

void Coin::setPosition(const glm::vec2 &pos) {
	posPlayer = pos;
	sprite->setPosition(pos);
}

glm::vec2 Coin::getPosition() {
	return posPlayer;
}

void Coin::setPlayer(Player *playerAux) {
	player = playerAux;
}

void Coin::restart() {
	posPlayer = iniPosition;
	sprite->setPosition(posPlayer);
}