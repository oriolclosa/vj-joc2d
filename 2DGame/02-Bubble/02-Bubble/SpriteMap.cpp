#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "SpriteMap.h"


using namespace std;

SpriteMap *SpriteMap::createSpriteMap(const char *tilesmapAux, const glm::ivec2 mapSizeAux, const glm::ivec2 tilesheetSizeAux, const glm::vec2 &minCoords, ShaderProgram &program)
{
	SpriteMap *map = new SpriteMap(tilesmapAux, mapSizeAux, tilesheetSizeAux, minCoords, program);
	return map;
}

SpriteMap::SpriteMap(const char *tilesmapAux, const glm::ivec2 mapSizeAux, const glm::ivec2 tilesheetSizeAux, const glm::vec2 &minCoords, ShaderProgram &program)
{
	mapSprites = tilesmapAux;
	mapSize = mapSizeAux;
	tilesheetSize = tilesheetSizeAux;

	Texture spritesheet;
	spritesheet.loadFromFile("images/margaret/floor.png", TEXTURE_PIXEL_FORMAT_RGBA);
	Sprite *sprites[1];
	sprites[0] = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(1, 1), &spritesheet, &program);
}

SpriteMap::~SpriteMap()
{
	if (mapSprites != NULL)
		delete mapSprites;
}

void SpriteMap::render() const{
	for (int j = 0; j < mapSize.y; j++) {
		for (int i = 0; i < mapSize.x; i++) {
			char tile = mapSprites[j * mapSize.x + i];
			if (tile >= '0' && tile <= '0') {
				int tileAct = tile - int(0);
				glm::vec2 texCoordTile = glm::vec2(float((tileAct - 1) % tilesheetSize.x) / tilesheetSize.x, float((tileAct - 1) / tilesheetSize.x) / tilesheetSize.y);
				//sprites[0]->setPosition(texCoordTile);
				//sprites[0]->render();
			}
		}
	}
}