
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
#include <glm/gtc/type_ptr.hpp>
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
    camera.loadPipeline(pipeline);
  });

  std::string vert = std::string(shaderCloudVert.data(), shaderCloudVert.size());
  std::string frag = std::string(shaderCloudFrag.data(), shaderCloudFrag.size());

  pipeline.compile(vert, frag);
  pipeline.bindAttrib(0, "position");
  pipeline.link();

  camera.loadPipeline(pipeline);

  sh::Entity entity;
  entity.pos = glm::vec3(0, 0, -2);

  r::Mesh mesh;
  std::vector<float> vertices = {
    -0.5f, 0.5f, 0.f,
    -0.5f, -0.5f, 0.f,
    0.5f, -0.5f, 0.f,
    0.5f, -0.5f, 0.f,
    0.5f, 0.5f, 0.f,
    -0.5f, 0.5f, 0.f
  };

  mesh.loadVertexData(vertices);
  std::cout << mesh.getVertexCount() << std::endl;

	while (!display.shouldClose()) {
    glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1.f, 0.f, 0.f, 1.f);

    pipeline.use();
    entity.pos += glm::vec3(0, 0, -0.1f);

    pipeline.transform(entity);

    mesh.bind();
    glDrawArrays(GL_TRIANGLES, 0, mesh.getVertexCount());
    mesh.release();
    r::unuse();
    
		display.poll();
	}
}
