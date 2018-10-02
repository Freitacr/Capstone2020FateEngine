#version 330 core
out vec4 color;
in vec2 uv;

uniform sampler2D textureSampler;

void main() {
	color = texture(textureSampler, uv);
	if (color.a < .01)
		discard;
} 