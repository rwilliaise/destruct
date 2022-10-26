
#include "Camera.h"
#include <iostream>

namespace cl {
  
  glm::mat4 Camera::getViewMatrix() const {
    glm::mat4 translation = glm::translate(glm::identity<glm::mat4>(), pos);
    glm::mat4 rotation = glm::mat4_cast(rot);

    return translation * rotation;
  }

  void Camera::loadProjection(r::Pipeline& pipeline) const {
    GLint proj = pipeline.getUniform("projection");

    if (proj == -1) {
      return;
    }

    pipeline.use();
    glUniformMatrix4fv(proj, 1, GL_FALSE, glm::value_ptr(getProjectionMatrix()));
    r::unuse();
  }

  void Camera::loadView(r::Pipeline &pipeline) const {
    GLint view = pipeline.getUniform("view");

    if (view == -1) {
      return;
    }

    glUniformMatrix4fv(view, 1, GL_FALSE, glm::value_ptr(getViewMatrix()));
  }
} // cl
