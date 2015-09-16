#include "components/FPScamera.h"

#include "glm/glm.hpp"

#include "cameras/Camera.h"
#include "input/Input.h"

FPSCamera::FPSCamera( Input &input ) : input( &input )
{
	input.onMouseMove.add( std::bind( &FPSCamera::mouseMoved, this, std::placeholders::_1, std::placeholders::_2 ) );
}

void FPSCamera::update()
{
	Camera *camera = dynamic_cast< Camera* >( object );

	glm::vec3 newPos = camera->position;

	if( input->isButtonDown( STRAFE_LEFT ) )
	{
		newPos -= camera->right * 0.1f;
	}
	if( input->isButtonDown( STRAFE_RIGHT ) )
	{
		newPos += camera->right * 0.1f;
	}
	if( input->isButtonDown( MOVE_FORWARD ) )
	{
		newPos += camera->direction * 0.1f;
	}
	if( input->isButtonDown( MOVE_BACKWARDS ) )
	{
		newPos -= camera->direction * 0.1f;
	}

	camera->setPosition( newPos );
}

void FPSCamera::mouseMoved( int xRel, int yRel )
{
	Camera *camera = dynamic_cast< Camera* >( object );

	glm::vec3 newRot = camera->rotation;

	newRot.x -= yRel * 0.01f;
	newRot.y -= xRel * 0.01f;

	camera->setRotation( newRot );
}