#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Desk.h"
#include "Game.h"

void Desk::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram){
	spritesheet.setWrapS(GL_MIRRORED_REPEAT);
	spritesheet.loadFromFile("images/margaret/desk1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 48), glm::vec2(1, 1), &spritesheet, &shaderProgram);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posClock.x), float(tileMapDispl.y + posClock.y)));
}


void Desk::update(int deltaTime){
	sprite->update(deltaTime);
	int sx = posClock.x;
	int sy = posClock.y;
	int anim = sprite->animation();
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posClock.x), float(tileMapDispl.y + posClock.y)));
}

void Desk::render(){
	sprite->render();
}

void Desk::setPlayer(Player *p){
	player = p;
}

void Desk::setPosition(const glm::vec2 &pos){
	posClock = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posClock.x), float(tileMapDispl.y + posClock.y)));
}

void Desk::setTarget(const glm::vec2 &pos){
	target = pos;
}