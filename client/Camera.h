
#pragma once

#include "Shader.h"
#include "Util.h"

#include <glm/ext/quaternion_trigonometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define DESTRUCT_CAMERA_NEARZ 0.1f
#define DESTRUCT_CAMERA_FARZ 1000.0f

namespace cl {
	
	/**
	 * Helper class to seperate some projection and view matrix calculations out
	 * of r::Pipeline and main.cpp.
	 */
	class Camera {
	public:
		
		/** Calculate view matrix from current position and rotation. */
		glm::mat4 getViewMatrix() const;
		/** Load projection matrix uniform into shader pipeline. */
		void loadProjection(r::Pipeline& pipeline) const;
		/** Calculate view matrix, then load it into shader pipeline. */
		void loadView(r::Pipeline& pipeline) const;

		inline void recalculateProjection(float fovy, float aspect) {
			projection = glm::perspective(fovy, aspect, DESTRUCT_CAMERA_NEARZ, DESTRUCT_CAMERA_FARZ);
		}

		inline glm::mat4 getProjectionMatrix() const { return projection; }

		glm::vec3 pos = glm::vec3();
		glm::quat rot = sh::QUAT_FORWARD;
	private:
		/** Used to transform coordinates into perspective projected coordinates. */
		glm::mat4 projection = glm::identity<glm::mat4>();
	};
}

