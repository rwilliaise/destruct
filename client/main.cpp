
#include "Entity.h"
#include "Render.h"
#include "Display.h"
#include "Mesh.h"
#include "Shader.h"
#include "Util.h"
#include "Camera.h"

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <glad/gl.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_transform.hpp>
#include <glm/ext/quaternion_trigonometric.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <stdio.h>

static auto shaderCloudVert = VEC_EMBEDDED_RESOURCE(cloud_vert);
static auto shaderCloudFrag = VEC_EMBEDDED_RESOURCE(cloud_frag);

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
  puts("Starting!");

  glfwSetErrorCallback(displayErrorCallback);
  
	if (glfwInit() == GLFW_FALSE) {
		return -1;
	}

  r::Display display;
  cl::Camera camera;
  camera.recalculateProjection(glm::radians(70.f), display.getAspect());

  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(rendererErrorCallback, 0);

  r::Pipeline pipeline;

  display.setFramebufferSizeCallback([&camera, &pipeline](int width, int height) {
    camera.recalculateProjection(glm::radians(70.f), (float) width / height);
    camera.loadProjection(pipeline);
  });

  std::string vert = std::string(shaderCloudVert.data(), shaderCloudVert.size());
  std::string frag = std::string(shaderCloudFrag.data(), shaderCloudFrag.size());

  pipeline.compile(vert, frag);
  pipeline.bindAttrib(0, "position");
  pipeline.link();

  camera.loadProjection(pipeline);

  sh::Entity entity;
  entity.pos = glm::vec3(0, 0, -2);

  r::Mesh mesh;
  std::vector<float> vertices = {
    -0.5f, 0.5f, 0.f,
    -0.5f, -0.5f, 0.f,
    0.5f, -0.5f, 0.f,
    0.5f, 0.5f, 0.f,
  };

  std::vector<float> uv = {
    0.f, 0.f,
    0.f, 1.f,
    1.f, 0.f,
    1.f, 1.f,
  };

  std::vector<int> index = {
    0,1,3,
    3,1,2
  };  

  mesh.loadIndices(index);
  mesh.loadVertexData(vertices);
  mesh.loadUVData(uv);
  std::cout << mesh.getVertexCount() << std::endl;

  glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);
  glm::quat uprot = glm::angleAxis(glm::radians(1.f), up);

	while (!display.shouldClose()) {
    glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1.f, 0.f, 0.f, 1.f);

    entity.pos += glm::vec3(0, 0, -0.1f);
    camera.rot *= uprot;
    pipeline.use();

    camera.loadView(pipeline);
    pipeline.transform(entity);

    mesh.bind();
    glDrawElements(GL_TRIANGLES, mesh.getVertexCount(), GL_UNSIGNED_INT, 0);
    mesh.release();

    r::unuse();
    
		display.poll();
	}
}
