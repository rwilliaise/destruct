
#pragma once

#include "Util.h"
#include <glm/common.hpp>
#include <glm/gtc/quaternion.hpp>

namespace sh {

	class Entity {
	public:
		// Entity();

		inline glm::mat4 toModelMatrix() const {
			glm::mat4 translate = glm::translate(glm::identity<glm::mat4>(), pos);
			glm::mat4 rotate = glm::mat4_cast(rot);

			return translate * rotate;
		}
		
		glm::vec3 pos = glm::vec3();
		glm::quat rot = QUAT_FORWARD;
	};
} // sh

