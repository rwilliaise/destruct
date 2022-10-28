#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 norm;

out vec2 r_uv;
out vec3 r_brightness;

uniform mat4 projection;
uniform mat4 transformation;
uniform mat4 view;

void main(void) {
  vec3 surfaceNormal = (transformation * vec4(norm, 0.0)).xyz;
  float prod = (1 - dot(surfaceNormal, vec3(0,0,-1))) * 0.5;

  gl_Position = projection * view * transformation * vec4(position, 1.0);
  r_uv = uv;
  r_brightness = vec3(prod, prod, prod);
}


