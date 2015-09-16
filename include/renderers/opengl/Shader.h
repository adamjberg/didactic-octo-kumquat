#pragma once

#include <string>

#include "GL.h"

class Shader
{
public:
	Shader( GLenum type, std::string filename );

	void fromFile( GLenum type, std::string filename );
	void fromSource( GLenum type, std::string source );
	std::string getShaderLog();

	GLuint id;
	GLint compiled;
};