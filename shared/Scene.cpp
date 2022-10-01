
#include "Scene.h"
#include <cstdint>
#include <utility>

namespace sh {

	bool Scene::ClaimEntity(EntityId& out) {
		if (alive >= MAX_ENTITIES) { return false; }
		EntityId i, curr;
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
		
		components.erase(ent);
		entities[ent].set(0, false);
		alive--;
	}

	bool Scene::AddComponent(uint32_t ent, ComponentType t, void *data) {

	}

	bool Scene::RemoveComponent(uint32_t ent, ComponentType t) {

	}

	void *Scene::GetComponent(uint32_t ent, ComponentType t) {

	}
} // sh
