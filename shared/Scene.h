
#ifndef DESTRUCT_SCENE_H
#define DESTRUCT_SCENE_H

#include <vector>
#include <bitset>
#include <unordered_map>
#include <inttypes.h>

namespace sh {
	
	const auto MAX_ENTITIES = 4096;
	const auto MAX_COMPONENTS = 32;
	// bit 0 reserved for claiming
	using Entity = std::bitset<MAX_COMPONENTS>;
	using EntityId = uint32_t;
	using ComponentType = uint8_t;
	using Components = std::array<void*, MAX_COMPONENTS - 1>;

	class Scene {
	public:
		bool ClaimEntity(EntityId& out);
		void DropEntity(EntityId ent);

		bool AddComponent(EntityId ent, ComponentType t, void *data);
		bool RemoveComponent(EntityId ent, ComponentType t);

		void *GetComponent(EntityId ent, ComponentType t);
	private:
		Entity entities[MAX_ENTITIES];
		std::unordered_map<EntityId, Components> components;
		uint32_t alive{};
	};
}

#endif // DESTRUCT_SCENE_H
