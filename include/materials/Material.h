#pragma once

#include "GL.h"

#include <string>

#include "renderers/opengl/GLUniform.h"
#include "renderers/opengl/Program.h"

#include "textures/Texture.h"

class Material
{
public:
	Material( Program *program, Texture *texture );

	void addUniform( GLUniform *uniform );

	Program *program;

	std::map<std::string, GLUniform *> uniforms;

	Texture *texture;

	GLboolean depthTest;
	GLboolean depthWrite;

	GLboolean colorWrite;

	GLboolean polygonOffset;
	GLfloat polygonOffsetFactor;
	GLfloat polygonOffsetUnits;

	bool visible;
	bool needsUpdate;
};