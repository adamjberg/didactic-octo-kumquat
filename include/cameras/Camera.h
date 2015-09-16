#pragma once

#include "core/Object3D.h"

#include "glm/glm.hpp"

class Camera : public Object3D
{
public:
	Camera( float fov = 45, float aspect = 1.0f, float near = 0.1f, float far = 2000 );

	void updateMatrix();
	void updateProjectionMatrix();

	glm::mat4 projectionMatrix;
	glm::vec3 direction;
	glm::vec3 right;

	float fov, aspect, near, far;
};