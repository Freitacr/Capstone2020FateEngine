#version 330 core 

layout(location = 0) in vec3 vertexPosition_model;
layout(location = 2) in vec2 vertexUV;
out vec2 uv;

void main() {
	gl_Position.xyz = vertexPosition_model;
	gl_Position.w = 1.0;
	uv = vertexUV;
}