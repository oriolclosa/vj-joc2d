#ifndef _SPRITE_MAP_INCLUDE
#define _SPRITE_MAP_INCLUDE


#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"


class SpriteMap
{

public:
	static SpriteMap *createSpriteMap(const char *map, const glm::vec2 &minCoords, ShaderProgram &program);

	SpriteMap(const char *map, const glm::vec2 &minCoords, ShaderProgram &program);
	~SpriteMap();

private:
	char *map;
};

#endif // _SPRITE_MAP_INCLUDE
