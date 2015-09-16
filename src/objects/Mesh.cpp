#include "objects/Mesh.h"

Mesh::Mesh()
{

}

Mesh::Mesh( Geometry &geometry, Material &material ) :
Object3D(),
geometry( &geometry ),
material( &material )
{

}

void Mesh::init( Geometry &geometry, Material &material )
{
	this->geometry = &geometry;
	this->material = &material;
}

GLuint Mesh::getVAO()
{
	return geometry->VAO;
}