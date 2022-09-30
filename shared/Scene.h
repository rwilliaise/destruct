
#ifndef DESTRUCT_SCENE_H
#define DESTRUCT_SCENE_H

#include <vector>
#include <bitset>
#include <inttypes.h>

namespace sh {
	
	const auto MAX_ENTITIES = 4096;
	const auto MAX_COMPONENTS = 32;
	// bit 0 reserved for claiming
	using Entity = std::bitset<MAX_COMPONENTS>;
	using ComponentType = uint8_t;

	class Scene {
	public:
		bool ClaimEntity(uint32_t& out);
		void DropEntity(uint32_t ent);

		bool AddComponent(uint32_t ent, ComponentType t, void *data);
		bool RemoveComponent(uint32_t ent, ComponentType t);

		void *GetComponent(uint32_t ent, ComponentType t);
	private:
		Entity entities[MAX_ENTITIES];
		void *entComponents[MAX_ENTITIES][MAX_COMPONENTS - 1];
		uint32_t alive{};
	};
}

#endif // DESTRUCT_SCENE_H
