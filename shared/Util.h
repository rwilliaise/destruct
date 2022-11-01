
#pragma once 

#include <LinearMath/btVector3.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#define VEC_EMBEDDED_RESOURCE(v) ([]() {															\
	extern char _binary_##v##_start, _binary_##v##_end;									\
	return std::vector<char>(&_binary_##v##_start, &_binary_##v##_end); \
})()

#define VEC_DBG(VECTOR) std::cout << "DEBUG: " #VECTOR " (" << VECTOR.size() << " elements) = {"; \
	for (auto dbgElement_ ## VECTOR : VECTOR ) {																										\
		std::cout << dbgElement_ ## VECTOR << ", ";																										\
	}																																																\
	std::cout << "}" << std::endl

#define VEC_DBG_S(VECTOR, CAST) std::cout << "DEBUG: " #VECTOR " (" << VECTOR.size() << " elements) = {" << std::endl; \
	for (auto dbgElement_ ## VECTOR : VECTOR ) {																											\
		std::cout << "	" << CAST(dbgElement_ ## VECTOR) << "," << std::endl;																		\
	}																																																	\
	std::cout << "}" << std::endl

namespace sh {
	const glm::vec3 VEC_FORWARD = glm::vec3(0.f, 0.f, -1.f);
	const glm::quat QUAT_FORWARD = glm::quat(glm::radians(0.f), VEC_FORWARD);

	btVector3 toBtVec(const glm::vec3 &vec);
	glm::vec3 fromBtVec(const btVector3 &vec);
} // sh

