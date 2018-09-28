#version 330 core
out vec3 color;
in vec2 uv;

uniform sampler2D textureSampler;

void main() {
	color = texture(textureSampler, uv).rgb;
} 