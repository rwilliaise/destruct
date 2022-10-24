#version 330 core

layout (location = 0) in vec3 position;

out vec3 color;

uniform mat4 projection;
uniform mat4 transformation;

void main() {
  gl_Position = projection * transformation * vec4(position, 1.0);
  color = vec3(position.x + 0.5, 0.0, position.y + 0.5);
}


