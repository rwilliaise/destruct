
#ifndef DESTRUCT_CAMERA_H
#define DESTRUCT_CAMERA_H

#include "Shader.h"

#include <glm/ext/quaternion_trigonometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define DESTRUCT_CAMERA_NEARZ 0.1f
#define DESTRUCT_CAMERA_FARZ 1000.0f

namespace cl {
  
  class Camera {
  public:
    //Camera();
    
    glm::mat4 getViewMatrix() const;
    void loadProjection(r::Pipeline& pipeline) const;
    void loadView(r::Pipeline& pipeline) const;

    inline void recalculateProjection(float fovy, float aspect) {
      projection = glm::perspective(fovy, aspect, DESTRUCT_CAMERA_NEARZ, DESTRUCT_CAMERA_FARZ);
    }

    inline glm::mat4 getProjectionMatrix() const { return projection; }

    glm::vec3 pos = glm::vec3();
    glm::quat rot = glm::angleAxis(glm::radians(0.f), glm::vec3(0.f, 0.f, -1.f));
  private:
    glm::mat4 projection = glm::identity<glm::mat4>();
  };
}

#endif // DESTRUCT_CAMERA_H
