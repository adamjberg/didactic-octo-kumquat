#version 330

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelViewProjectionMatrix;

in vec3 position;
in vec2 uv;
in vec3 normal;

out vec3 normal_camera;
out vec3 vertex_position_camera;
out vec3 light_position_camera;

void main () {
	vec3 lightPosition = vec3(0.0, 10.0, 0.0);
	mat3 normalMatrix = mat3( transpose(inverse(modelViewMatrix)) ); 

	light_position_camera = vec3(viewMatrix * vec4(lightPosition, 1.0));
	vertex_position_camera = vec3(modelViewMatrix * vec4(position, 1.0));
	normal_camera = normalize(normalMatrix * normal);

	gl_Position = modelViewProjectionMatrix * vec4 (position, 1.0);
}