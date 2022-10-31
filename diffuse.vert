#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 norm;

out vec2 r_uv;
out vec3 r_brightness;

uniform mat4 projection;
uniform mat4 transformation;
uniform mat4 view;

const vec3 LIGHT_POS = vec3(0, 0, 0);
const vec3 LIGHT_COLOR = vec3(1, 1, 1);
const vec3 LIGHT_ATTENUATION = vec3(1.f, 0.1f, 0.002f);

void main(void) {
  vec4 wPos = transformation * vec4(position, 1.0);
  vec3 surfaceNormal = normalize((transformation * vec4(norm, 0.0)).xyz);
  vec3 lightDifference = wPos.xyz - LIGHT_POS;

  float diffLength = length(lightDifference);
  float prod = (1 - dot(surfaceNormal, lightDifference / diffLength)) * 0.5;
  float attenuation = LIGHT_ATTENUATION.x + (LIGHT_ATTENUATION.y * diffLength) + (LIGHT_ATTENUATION.z * diffLength * diffLength);
  float bright = prod / attenuation;

  gl_Position = projection * view * wPos;

  r_uv = uv;
  r_brightness = bright * LIGHT_COLOR;
}


