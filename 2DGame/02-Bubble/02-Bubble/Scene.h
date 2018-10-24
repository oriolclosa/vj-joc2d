#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"

#include "Quad.h"
#include "TexturedQuad.h"
#include "Text.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();

private:
	void initShaders();

private:
	TileMap *map;
	TileMap *assetmap;
	Player *player;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;	
	Texture texs[2];
	TexturedQuad *texQuad[3];
	Text text;

};


#endif // _SCENE_INCLUDE

