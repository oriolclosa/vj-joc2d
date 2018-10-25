#ifndef _SPRITE_MAP_INCLUDE
#define _SPRITE_MAP_INCLUDE


#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"
#include "Sprite.h"
#include "Desk.h"


class SpriteMap
{

public:
	static SpriteMap *createSpriteMap(const char *map, const glm::ivec2 mapSize, const glm::ivec2 tilesheetSize, const glm::vec2 &minCoords, ShaderProgram &program);

	SpriteMap(const char *map, const glm::ivec2 mapSize, const glm::ivec2 tilesheetSize, const glm::vec2 &minCoords, ShaderProgram &program);
	~SpriteMap();

	void render() const;

private:
	const char *mapSprites;
	glm::ivec2 mapSize, tilesheetSize;
	Desk *desk;
};

#endif // _SPRITE_MAP_INCLUDE
