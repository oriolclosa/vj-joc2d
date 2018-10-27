#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Blocking.h"
#include "Game.h"
#include "Level.h"


void Blocking::init(ShaderProgram &shaderProgram, glm::vec2 pos) {
	spritesheet.loadFromFile("images/margaret/train.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(64, 582), glm::vec2(1.0f, 1.0f), &spritesheet, &shaderProgram);
	iniPosition = pos;
}

void Blocking::update(int deltaTime) {
	sprite->update(deltaTime);
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