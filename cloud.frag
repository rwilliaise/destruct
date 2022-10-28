#version 330 core

in vec2 r_uv;
out vec4 out_Color;

uniform sampler2D loadedTexture;

void main(void) {
  out_Color = texture(loadedTexture, r_uv);
}
