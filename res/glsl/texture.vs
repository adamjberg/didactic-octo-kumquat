#version 330

uniform mat4 modelViewProjectionMatrix;

in vec3 position;
in vec2 uv;

out vec2 vUV;

void main () {
	vUV = uv;

	gl_Position = modelViewProjectionMatrix * vec4 (position, 1.0);
}