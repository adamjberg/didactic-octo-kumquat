#pragma once

#include "core/Geometry.h"
#include "core/Object3D.h"
#include "materials/Material.h"

class Mesh : public Object3D
{
public:
	Mesh();
	Mesh( Geometry &geometry, Material &material );

	void init( Geometry &geometry, Material &material );

	GLuint getVAO();

	Geometry *geometry;
	Material *material;
};