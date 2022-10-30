
#include "Entity.h"
#include "Render.h"
#include "Display.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Util.h"
#include "Camera.h"

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <cstdio>
#include <ctime>
#include <glad/gl.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_transform.hpp>
#include <glm/ext/quaternion_trigonometric.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

static constexpr int MOUSE_LOOK_SCALE = 5;

static auto shaderCloudVert = VEC_EMBEDDED_RESOURCE(cloud_vert);
static auto shaderCloudFrag = VEC_EMBEDDED_RESOURCE(cloud_frag);
static auto gregolanJrTxt = VEC_EMBEDDED_RESOURCE(gregolan_jr_png);
static auto gregolanJr = VEC_EMBEDDED_RESOURCE(gregolan_jr_obj);

static void displayErrorCallback(int errorCode, const char *description) {
  std::cerr << "GLFW ERROR (" << errorCode << "): " << description << std::endl;
}

static void rendererErrorCallback(GLenum source,
                                  GLenum type,
                                  GLuint id,
                                  GLenum severity,
                                  GLsizei length,
                                  const char *msg,
                                  const void *user) {
  fprintf(type == GL_DEBUG_TYPE_ERROR ? stderr : stdout, "GL %s (0x%x, 0x%x): %s\n", type == GL_DEBUG_TYPE_ERROR ? "ERROR" : "INFO", type, severity, msg);
}

int main() {
  glfwSetErrorCallback(displayErrorCallback);
  
	if (glfwInit() == GLFW_FALSE) {
		return -1;
	}

  r::Display display;
  cl::Camera camera;
  camera.recalculateProjection(glm::radians(50.f), display.getAspect());

  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(rendererErrorCallback, 0);

  r::Pipeline pipeline;

  display.setFramebufferSizeCallback([&](int width, int height) {
    camera.recalculateProjection(glm::radians(50.f), (float) width / height);
    camera.loadProjection(pipeline);
  });

  std::string vert = std::string(shaderCloudVert.data(), shaderCloudVert.size());
  std::string frag = std::string(shaderCloudFrag.data(), shaderCloudFrag.size());

  pipeline.compile(vert, frag);
  pipeline.bindAttrib(0, "position");
  pipeline.link();

  camera.loadProjection(pipeline);

  sh::Entity entity;
  entity.pos = glm::vec3(0, 0, -10);

  r::Mesh mesh;
  mesh.loadFromMemory(gregolanJr);

  glm::vec3 up = glm::vec3(0.f, -1.f, 0.f);
  glm::quat targetRot = sh::QUAT_FORWARD;

  display.setCursorPosCallback([&](double x, double y) {
    int width, height;
    glfwGetFramebufferSize(display.get(), &width, &height);

    // from -1 to 1
    double xRatio = -(x / width - 0.5) * 2;
    double yRatio = (y / height - 0.5) * 2;
    double aspect = display.getAspect();

    glm::vec3 target = glm::vec3(xRatio * aspect * MOUSE_LOOK_SCALE, yRatio * MOUSE_LOOK_SCALE, -MOUSE_LOOK_SCALE); 

    targetRot = glm::quatLookAt(glm::normalize(target - entity.pos), up);
  });

  r::Texture texture;
  texture.loadFromBytes(std::vector<uint8_t>(gregolanJrTxt.begin(), gregolanJrTxt.end()));

  glEnable(GL_MULTISAMPLE);

  double lastTime = std::clock();

	while (!display.shouldClose()) {
    double delta = (std::clock() - lastTime) / CLOCKS_PER_SEC;
    lastTime = std::clock();
    
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.f, 0.f, 0.f, 1.f);

    entity.rot = glm::slerp(entity.rot, targetRot, std::min(10.f * static_cast<float>(delta), 0.5f));

    pipeline.use();

    camera.loadView(pipeline);
    pipeline.transform(entity);

    glActiveTexture(GL_TEXTURE0);
    texture.bind();
    mesh.draw();
    texture.release();

    r::unuse();
    
		display.poll();
	}
}
