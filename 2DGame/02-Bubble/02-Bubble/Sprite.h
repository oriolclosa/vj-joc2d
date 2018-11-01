#ifndef _SPRITE_INCLUDE
#define _SPRITE_INCLUDE


#include <vector>
#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"
#include "AnimKeyframes.h"


// This class is derived from code seen earlier in TexturedQuad but it is also
// able to manage animations stored as a spritesheet. 


class Sprite{

public:
	// Textured quads can only be created inside an OpenGL context
	static Sprite *createSprite(const glm::vec2 &quadSize, const glm::vec2 &sizeInSpritesheet, Texture *spritesheet, ShaderProgram *program);

	Sprite(const glm::vec2 &quadSize, const glm::vec2 &sizeInSpritesheet, Texture *spritesheet, ShaderProgram *program);

	void update(int deltaTime);
	void update(float totalTime, int deltaTime);
	void render() const;
	void free();

	void setNumberAnimations(int nAnimations);
	void setAnimationSpeed(int animId, int keyframesPerSec);
	void addKeyframe(int animId, const glm::vec2 &frame);
	void changeAnimation(int animId);
	int animation() const;
	
	void setPosition(const glm::vec2 &pos);
	void setSize(const glm::vec2 &sizeAux);

	void lookRight(bool right);

	void resetToAnimation(float timeToIni, float timeTo, int animTo);
	void moveToAt(float timeToIni, float timeTo, glm::vec2 positionTo);

	void setBottomPosition(glm::vec2 positionAux);

	void setHit(bool activate);


private:
	Texture *texture;
	ShaderProgram *shaderProgram;
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	glm::vec2 position;
	int currentAnimation, currentKeyframe, resetToAnim;
	float timeAnimation, resetToTime, resetToTimeIni, moveToTime, moveToTimeIni;
	glm::vec2 texCoordDispl, moveTo;
	vector<AnimKeyframes> animations;

	bool right;
	glm::vec2 size;
	bool hit;
	int hit_time;
};


#endif // _SPRITE_INCLUDE

