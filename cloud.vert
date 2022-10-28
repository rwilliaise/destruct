#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 norm;

//out vec2 r_uv;
out vec3 r_color;

uniform mat4 projection;
uniform mat4 transformation;
uniform mat4 view;

void main(void) {
  gl_Position = projection * view * transformation * vec4(position, 1.0);
  //r_uv = uv;
  r_color = norm;
}


