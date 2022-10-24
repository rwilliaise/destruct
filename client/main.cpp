
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
  printf("GLFW ERROR (%d): %s\n", errorCode, description);
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

  display.setFramebufferSizeCallback([&camera](int width, int height) {
    camera.recalculateProjection(glm::radians(70.f), (float) width / height);
  });

  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(rendererErrorCallback, 0);

  r::Pipeline pipeline;

  std::string vert = std::string(shaderCloudVert.data(), shaderCloudVert.size());
  std::string frag = std::string(shaderCloudFrag.data(), shaderCloudFrag.size());

  pipeline.compile(vert, frag);
  pipeline.bindAttrib(0, "position");
  pipeline.link();

  glm::mat4 transformation = glm::identity<glm::mat4>();
  transformation = glm::translate(transformation, glm::vec3(0, 0, -2));

  GLint proj = pipeline.getUniform("projection");
  GLint trans = pipeline.getUniform("transformation");

  pipeline.use();
  glUniformMatrix4fv(proj, 1, GL_FALSE, glm::value_ptr(camera.getProjectionMatrix()));
  glUniformMatrix4fv(trans, 1, GL_FALSE, glm::value_ptr(transformation));
  r::unuse();

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
    
    transformation = glm::rotate(transformation, glm::radians(1.f), glm::vec3(0.f, 1.f, 0.f));

    pipeline.use();
    glUniformMatrix4fv(trans, 1, GL_FALSE, glm::value_ptr(transformation));
    mesh.bind();
    glDrawArrays(GL_TRIANGLES, 0, mesh.getVertexCount());
    mesh.release();
    r::unuse();
    
		display.poll();
	}
}
