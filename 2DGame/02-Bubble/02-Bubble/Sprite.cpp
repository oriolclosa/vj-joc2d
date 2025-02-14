#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Sprite.h"
#include "Game.h"


Sprite *Sprite::createSprite(const glm::vec2 &quadSize, const glm::vec2 &sizeInSpritesheet, Texture *spritesheet, ShaderProgram *program)
{
	Sprite *quad = new Sprite(quadSize, sizeInSpritesheet, spritesheet, program);

	return quad;
}


Sprite::Sprite(const glm::vec2 &quadSize, const glm::vec2 &sizeInSpritesheet, Texture *spritesheet, ShaderProgram *program)
{
	float vertices[24] = {0.f, 0.f, 0.f, 0.f, 
												quadSize.x, 0.f, sizeInSpritesheet.x, 0.f, 
												quadSize.x, quadSize.y, sizeInSpritesheet.x, sizeInSpritesheet.y, 
												0.f, 0.f, 0.f, 0.f, 
												quadSize.x, quadSize.y, sizeInSpritesheet.x, sizeInSpritesheet.y, 
												0.f, quadSize.y, 0.f, sizeInSpritesheet.y};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), vertices, GL_STATIC_DRAW);
	posLocation = program->bindVertexAttribute("position", 2, 4*sizeof(float), 0);
	texCoordLocation = program->bindVertexAttribute("texCoord", 2, 4*sizeof(float), (void *)(2*sizeof(float)));
	texture = spritesheet;
	shaderProgram = program;
	currentAnimation = -1;
	resetToAnim = -1;
	resetToTime = 0.0f;
	moveToTime = -1.0f;
	moveTo = glm::vec2(0, 0);
	position = glm::vec2(0.f);
	size = quadSize;
	right = true;
	hit = false;
	hit_time = 0;
}

void Sprite::update(float totalTime, int deltaTime){
	if (hit_time > 0) --hit_time;
	else hit = false;
	if ((resetToAnim >= 0) && ((totalTime - resetToTimeIni) >= resetToTime)) {
		changeAnimation(resetToAnim);
		resetToAnim = -1;
	}
	else if ((moveToTime >= 0.0f) && ((totalTime - moveToTimeIni) >= moveToTime)) {
		moveToTime = -1.0f;
		position += moveTo;
		Game::instance().getScene().setPlayerPos(position);
		moveTo = glm::vec2(0, 0);
	}
	else if (currentAnimation >= 0) {
		timeAnimation += deltaTime;
		while (timeAnimation > animations[currentAnimation].millisecsPerKeyframe)
		{
			timeAnimation -= animations[currentAnimation].millisecsPerKeyframe;
			currentKeyframe = (currentKeyframe + 1) % animations[currentAnimation].keyframeDispl.size();
		}
		texCoordDispl = animations[currentAnimation].keyframeDispl[currentKeyframe];
	}
}

void Sprite::update(int deltaTime) {
	if (currentAnimation >= 0) {
		if (hit_time > 0) --hit_time;
		else hit = false;
		timeAnimation += deltaTime;
		while (timeAnimation > animations[currentAnimation].millisecsPerKeyframe)
		{
			timeAnimation -= animations[currentAnimation].millisecsPerKeyframe;
			currentKeyframe = (currentKeyframe + 1) % animations[currentAnimation].keyframeDispl.size();
		}
		texCoordDispl = animations[currentAnimation].keyframeDispl[currentKeyframe];
	}
}

void Sprite::render() const{
	glm::mat4 modelview = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f));
	if (!right) {
		modelview = glm::translate(glm::scale(modelview, glm::vec3(-1.0f, 1.0f, 1.0f)), glm::vec3(-size.x, 0.0f, 0.0f));
	}
	shaderProgram->setUniformMatrix4f("modelview", modelview);
	shaderProgram->setUniform2f("texCoordDispl", texCoordDispl.x, texCoordDispl.y);
	if (hit) shaderProgram->setUniform4f("color", 1.0f, .0f, .0f, 1.0f);
	else shaderProgram->setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	texture->use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisable(GL_TEXTURE_2D);
}

void Sprite::free()
{
	glDeleteBuffers(1, &vbo);
}

void Sprite::setNumberAnimations(int nAnimations)
{
	animations.clear();
	animations.resize(nAnimations);
}

void Sprite::setAnimationSpeed(int animId, int keyframesPerSec)
{
	if(animId < int(animations.size()))
		animations[animId].millisecsPerKeyframe = 1000.f / keyframesPerSec;
}

void Sprite::addKeyframe(int animId, const glm::vec2 &displacement)
{
	if(animId < int(animations.size()))
		animations[animId].keyframeDispl.push_back(displacement);
}

void Sprite::changeAnimation(int animId)
{
	if(animId < int(animations.size()))
	{
		currentAnimation = animId;
		currentKeyframe = 0;
		timeAnimation = 0.f;
		texCoordDispl = animations[animId].keyframeDispl[0];
	}
}

int Sprite::animation() const
{
	return currentAnimation;
}

void Sprite::setPosition(const glm::vec2 &pos)
{
	position = pos;
}

void Sprite::lookRight(bool rightAux) {
	right = !rightAux;
}

void Sprite::setSize(const glm::vec2 &sizeAux) {
	size = sizeAux;
}

void Sprite::resetToAnimation(float timeToIni, float timeTo, int animTo) {
	resetToTimeIni = timeToIni;
	resetToTime = timeTo;
	resetToAnim = animTo;
}

void Sprite::moveToAt(float timeToIni, float timeTo, glm::vec2 positionTo) {
	moveToTimeIni = timeToIni;
	moveToTime = timeTo;
	moveTo = positionTo;
}

void Sprite::setBottomPosition(glm::vec2 positionAux) {
	position = positionAux - glm::vec2(0, size.y);
}

void Sprite::setHit(bool activate) {
	if (activate) {
		hit = true;
		hit_time = 24;
	}
	else {
		hit = false;
		hit_time = 0;
	}
}