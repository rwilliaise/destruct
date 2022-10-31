#version 460 core

in vec2 r_uv;
in vec3 r_brightness;

out vec4 out_Color;

uniform sampler2D loadedTexture;

void main(void) {
  out_Color = vec4(r_brightness, 1.0) * texture(loadedTexture, r_uv);
}
