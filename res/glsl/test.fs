#version 330

in vec3 normal_camera;
in vec3 vertex_position_camera;
in vec3 light_position_camera;

out vec4 gl_FragColor;

void main () {
	vec3 ambientColor = vec3(0.2);
	vec3 diffuseColor = vec3(1.0, 0.0, 0.0);

	vec3 light_vert = normalize(light_position_camera - vertex_position_camera);
	vec3 light_refl = normalize(reflect(light_vert, normal_camera));

	float diffuse_intensity = clamp(dot(light_vert, normal_camera), 0.0, 1.0);

	gl_FragColor = vec4(ambientColor + diffuseColor * diffuse_intensity, 1.0);
}