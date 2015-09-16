#version 330

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;

in vec3 position;

void main ()
{
	gl_Position = modelViewProjectionMatrix * vec4 (position, 1.0);
}