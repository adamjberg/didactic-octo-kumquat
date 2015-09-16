#include "cameras/Camera.h"

Camera::Camera( float fov, float aspect, float near, float far ) : fov( fov ), aspect( aspect ), near( near ), far( far )
{
	rotation = glm::vec3( 0, 3.14f, 0 );
	updateProjectionMatrix();
}

void Camera::updateMatrix()
{
	float horizontalAngle = rotation.y;
	float verticalAngle = rotation.x;

	direction = glm::vec3(
		cos( verticalAngle ) * sin( horizontalAngle ),
		sin( verticalAngle ),
		cos( verticalAngle ) * cos( horizontalAngle )
		);
	right = glm::vec3(
		sin( horizontalAngle - 3.14f / 2.0f ),
		0,
		cos( horizontalAngle - 3.14f / 2.0f )
		);
	glm::vec3 up = glm::cross( right, direction );
	matrix = glm::lookAt( position, position + direction, up );
}

void Camera::updateProjectionMatrix()
{
	projectionMatrix = glm::perspective( fov, aspect, near, far );
}