
#ifndef DESTRUCT_WORLD_SPAWN_ENTITY_H
#define DESTRUCT_WORLD_SPAWN_ENTITY_H

#include "Entity.h"
#include "LinearMath/btVector3.h"
#include <string>

namespace sh {

	class WorldSpawnEntity : public Entity {
	public:
		WorldSpawnEntity(std::string name): mapName(name) {}

		bool loadMapData();

	private:
		std::string mapName;
		btVector3 vecData;
	};
} // sh

#endif // DESTRUCT_WORLD_SPAWN_ENTITY_H
