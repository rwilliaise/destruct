
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

// shaders
static auto diffuse_vert = VEC_EMBEDDED_RESOURCE(diffuse_vert);
static auto diffuse_frag = VEC_EMBEDDED_RESOURCE(diffuse_frag);

// textures
static auto gregolan_txt = VEC_EMBEDDED_RESOURCE(gregolan_png);
static auto gregolan_jr_txt = VEC_EMBEDDED_RESOURCE(gregolan_jr_png);

// models
static auto gregolan = VEC_EMBEDDED_RESOURCE(gregolan_obj);
static auto gregolan_jr = VEC_EMBEDDED_RESOURCE(gregolan_jr_obj);

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

	std::string vert = std::string(diffuse_vert.data(), diffuse_vert.size());
	std::string frag = std::string(diffuse_frag.data(), diffuse_frag.size());

	pipeline.compile(vert, frag);
	pipeline.link();

	camera.loadProjection(pipeline);

	sh::Entity gregolanJrEntity;
	sh::Entity gregolanEntity;
	gregolanJrEntity.pos = glm::vec3(3, 0, -10);
	gregolanEntity.pos = glm::vec3(-3, 0, -10);

	glm::vec3 up = glm::vec3(0.f, -1.f, 0.f);
	glm::quat gregolanJrTarget = sh::QUAT_FORWARD;
	glm::quat gregolanTarget = sh::QUAT_FORWARD;

	display.setCursorPosCallback([&](double x, double y) {
		int width, height;
		glfwGetFramebufferSize(display.get(), &width, &height);

		// from -1 to 1
		double xRatio = -(x / width - 0.5) * 2;
		double yRatio = (y / height - 0.5) * 2;
		double aspect = display.getAspect();

		glm::vec3 target = glm::vec3(xRatio * aspect * 4, yRatio * 4, -7); 
		gregolanJrTarget = glm::quatLookAt(glm::normalize(target - gregolanJrEntity.pos), up);
		gregolanTarget = glm::quatLookAt(glm::normalize(gregolanEntity.pos - target), up);
	});

	r::Mesh gregolanJrMesh;
	r::Mesh gregolanMesh;
	gregolanJrMesh.loadFromMemory(gregolan_jr);
	gregolanMesh.loadFromMemory(gregolan);

	r::Texture gregolanJrTexture;
	r::Texture gregolanTexture;
	gregolanJrTexture.loadFromBytes(std::vector<uint8_t>(gregolan_jr_txt.begin(), gregolan_jr_txt.end()));
	gregolanTexture.loadFromBytes(std::vector<uint8_t>(gregolan_txt.begin(), gregolan_txt.end()));

	glEnable(GL_MULTISAMPLE);

	double lastTime = std::clock();

	while (!display.shouldClose()) {
		double delta = (std::clock() - lastTime) / CLOCKS_PER_SEC;
		lastTime = std::clock();
		
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.f, 0.f, 0.f, 1.f);

		gregolanJrEntity.rot = glm::slerp(gregolanJrEntity.rot, gregolanJrTarget, std::min(10.f * static_cast<float>(delta), 0.5f));
		gregolanEntity.rot = glm::slerp(gregolanEntity.rot, gregolanTarget, std::min(10.f * static_cast<float>(delta), 0.5f));

		pipeline.use();

		camera.loadView(pipeline);
		glActiveTexture(GL_TEXTURE0);
		
		pipeline.transform(gregolanJrEntity);
		gregolanJrTexture.bind();
		gregolanJrMesh.draw();
		gregolanJrTexture.release();

		pipeline.transform(gregolanEntity);
		gregolanTexture.bind();
		gregolanMesh.draw();
		gregolanTexture.release();

		r::unuse();
		
		display.poll();
	}
}
