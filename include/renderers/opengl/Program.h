#pragma once

#include <map>
#include <string>
#include <vector>

#include "GL.h"

#include "renderers/opengl/GLUniform.h"

class Program
{
public:
	Program::Program( std::string vertexShaderFilename, std::string fragmentShaderFilename );
	~Program();

	void addUniform( GLUniform *uniform );
	GLUniform* getUniform( std::string name );

	std::string log;

	GLint id;
	GLint linked;

	std::map<std::string, GLUniform*>uniforms;
};