
#ifndef DESTRUCT_ENTITY_H
#define DESTRUCT_ENTITY_H

#include <glm/common.hpp>
#include <glm/gtc/quaternion.hpp>

namespace sh {

	class Entity {
	public:
		// Entity();

    inline glm::mat4 toModelMatrix() {
      glm::mat4 translate = glm::translate(glm::identity<glm::mat4>(), pos);
      glm::mat4 rotate = glm::mat4_cast(rot);
      return translate * rotate;
    }
		
    glm::vec3 pos = glm::vec3();
    glm::quat rot = glm::quat();
	};
} // sh

#endif // DESTRUCT_ENTITY_H
