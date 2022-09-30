
#include "Scene.h"
#include <cstdint>

namespace sh {

	bool Scene::ClaimEntity(uint32_t& out) {
		if (alive >= MAX_ENTITIES) { return false; }
		uint32_t i, curr;
		for (auto&& ent : entities) {
			curr = i++;
			if (ent.test(0)) {
				continue;
			}

			ent.set(0);
			alive++;
			out = curr;
			return true;
		}
		return false;
	}

	void Scene::DropEntity(uint32_t ent) {
		if (ent > MAX_ENTITIES) { return; }
		
		entities[ent].set(0, false);
		alive--;
	}
} // sh
