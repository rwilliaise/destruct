#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;

out vec3 color;

uniform mat4 projection;
uniform mat4 transformation;
uniform mat4 view;

void main() {
  gl_Position = projection * view * transformation * vec4(position, 1.0);
  color = vec3(position.x + 0.5, 0.0, position.y + 0.5);
}


