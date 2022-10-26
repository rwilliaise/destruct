
#ifndef DESTRUCT_UTIL_H
#define DESTRUCT_UTIL_H

#include <LinearMath/btVector3.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#define VEC_EMBEDDED_RESOURCE(v) ([]() {                              \
  extern char _binary_##v##_start, _binary_##v##_end;                 \
  return std::vector<char>(&_binary_##v##_start, &_binary_##v##_end); \
})()

namespace sh {
  const glm::vec3 VEC_FORWARD = glm::vec3(0.f, 0.f, -1.f);
  const glm::quat QUAT_FORWARD = glm::quat(glm::radians(0.f), VEC_FORWARD);

	btVector3 toBtVec(const glm::vec3 &vec);
	glm::vec3 fromBtVec(const btVector3 &vec);
} // sh

#endif // DESTRUCT_UTIL_H
