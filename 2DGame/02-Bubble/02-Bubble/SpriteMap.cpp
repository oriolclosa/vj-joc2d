#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "SpriteMap.h"


using namespace std;

SpriteMap *SpriteMap::createSpriteMap(const char *tilesmap, const glm::vec2 &minCoords, ShaderProgram &program)
{
	SpriteMap *map = new SpriteMap(tilesmap, minCoords, program);
	return map;
}

SpriteMap::SpriteMap(const char *tilesmap, const glm::vec2 &minCoords, ShaderProgram &program)
{
}

SpriteMap::~SpriteMap()
{
	if (map != NULL)
		delete map;
}

void SpriteMap::render() const
{
	
}