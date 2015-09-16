#include "core/Object3D.h"

Object3D::Object3D() : scale( glm::vec3( 1.0 ) ), rotation( glm::vec3( 0.0 ) ), needsUpdate( true )
{

}

Object3D::~Object3D()
{

}

void Object3D::add( Object3D &object )
{
	this->children.push_back( &object );
}

void Object3D::add( Component &component )
{
	component.object = this;
	this->components.push_back( &component );
}

void Object3D::update()
{
	if( needsUpdate )
	{
		updateMatrix();
		onUpdate.dispatch();

		needsUpdate = false;
	}

	for( Component *component : components )
	{
		component->update();
	}

	for( Object3D *child : children )
	{
		child->update();
	}
}

void Object3D::updateMatrix()
{
	matrix = glm::mat4();

	matrix = glm::rotate( matrix, rotation.x, glm::vec3( 1.0, 0.0, 0.0 ) );
	matrix = glm::rotate( matrix, rotation.y, glm::vec3( 0.0, 1.0, 0.0 ) );
	matrix = glm::rotate( matrix, rotation.z, glm::vec3( 0.0, 0.0, 1.0 ) );

	matrix = glm::scale( matrix, scale );

	matrix = glm::translate( matrix, position );
}

void Object3D::setPosition( glm::vec3 position )
{
	if( position != this->position )
	{
		this->position = position;
		needsUpdate = true;
		onPositionChanged.dispatch();
	}
}

void Object3D::setRotation( glm::vec3 rotation )
{
	if( rotation != this->rotation )
	{
		this->rotation = rotation;
		needsUpdate = true;
		onRotationChanged.dispatch();
	}
}

void Object3D::setScale( glm::vec3 scale )
{
	if( scale != this->scale )
	{
		this->scale = scale;
		needsUpdate = true;
		onScaleChanged.dispatch();
	}
}