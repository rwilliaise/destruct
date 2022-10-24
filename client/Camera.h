
#ifndef DESTRUCT_CAMERA_H
#define DESTRUCT_CAMERA_H

#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define DESTRUCT_CAMERA_NEARZ 0.1f
#define DESTRUCT_CAMERA_FARZ 1000.0f

namespace cl {
  
  class Camera {
  public:
    //Camera();

    inline void recalculateProjection(float fovy, float aspect) {
      projection = glm::perspective(fovy, aspect, DESTRUCT_CAMERA_NEARZ, DESTRUCT_CAMERA_FARZ);
    }

    inline glm::mat4 getProjectionMatrix() { return projection; }

  private:
    glm::mat4 projection = glm::identity<glm::mat4>();
    glm::vec3 pos;

    // glm::quat rot;
  };
}

#endif // DESTRUCT_CAMERA_H
