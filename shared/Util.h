
#ifndef DESTRUCT_UTIL_H
#define DESTRUCT_UTIL_H

#include <LinearMath/btVector3.h>
#include <glm/glm.hpp>

namespace sh {

	btVector3 toBtVec(const glm::vec3 &vec);
	glm::vec3 fromBtVec(const btVector3 &vec);
} // sh

#endif // DESTRUCT_UTIL_H
