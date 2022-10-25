
#ifndef DESTRUCT_ENTITY_H
#define DESTRUCT_ENTITY_H

#include <glm/common.hpp>
#include <glm/gtc/quaternion.hpp>

namespace sh {

	class Entity {
	public:
		Entity();
		
	private:
    glm::vec3 pos;
    glm::quat quat;
	};
} // sh

#endif // DESTRUCT_ENTITY_H
