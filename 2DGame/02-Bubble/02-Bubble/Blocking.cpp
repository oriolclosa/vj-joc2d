#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Blocking.h"
#include "Game.h"
#include "Level.h"

#define MOVE_DISTANCE 750


void Blocking::init(ShaderProgram &shaderProgram, glm::vec2 pos) {
	spritesheet.loadFromFile("images/margaret/train.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(64, 608), glm::vec2(1.0f, 1.0f), &spritesheet, &shaderProgram);
	iniPosition = pos;
	status = 0;
	moved = 0.0f;
}

void Blocking::update(int deltaTime) {
	sprite->update(deltaTime);
	cout << status << " " << moved << " " << posPlayer.x - playerPos.x << endl;
	if (status == 0) {
		if ((posPlayer.x - playerPos.x) < MOVE_DISTANCE) {
			status = 1;
		}
	}
	else if (status == 1) {
		if (moved > 400.0f) {
			status = 2;
		}
		else {
			moved += 2.5f;
			sprite->setPosition(posPlayer + glm::ivec2(0, int(moved)));
		}
	}
}

void Blocking::render() {
	sprite->render();
}

void Blocking::setPosition(const glm::vec2 &pos) {
	posPlayer = pos;
	sprite->setPosition(posPlayer);
}

glm::vec2 Blocking::getPosition() {
	return posPlayer;
}

void Blocking::restart() {
	posPlayer = iniPosition;
	sprite->setPosition(posPlayer);
}

void Blocking::setPlayerPos(glm::vec2 &playerPosAux) {
	playerPos = playerPosAux;
}