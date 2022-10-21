
#include "Util.h"
#include <LinearMath/btVector3.h>

namespace sh {
	
	btVector3 toBtVec(const glm::vec3 &vec) {
		return btVector3(vec.x, vec.y, vec.z);
	}

	glm::vec3 fromBtVec(const btVector3 &vec) {
		return glm::vec3(vec.x(), vec.y(), vec.z());
	}
} // sh
  
