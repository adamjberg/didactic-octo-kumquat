#include "renderers/opengl/Shader.h"

#include "utils/File.h"

#include "res_path.h"

Shader::Shader( GLenum type, std::string filename )
{
	fromFile( type, filename );
}

void Shader::fromFile( GLenum type, std::string filename )
{
	std::string shaderPath = getResourcePath("glsl");
	std::string source = readFile( shaderPath + filename );
	fromSource( type, source );
}

void Shader::fromSource( GLenum type, std::string source )
{
	id = glCreateShader( type );

	const char *shader_c_str = source.c_str();
	glShaderSource( id, 1, &shader_c_str, NULL );
	glCompileShader( id );

	glGetShaderiv( id, GL_COMPILE_STATUS, &compiled );
}

std::string Shader::getShaderLog()
{
	int infoLogLength = 0;
	int maxLength = infoLogLength;
	std::string log;
	log.reserve( maxLength );

	glGetShaderiv( id, GL_INFO_LOG_LENGTH, &maxLength );
	glGetShaderInfoLog( id, maxLength, &infoLogLength, &log[ 0 ] );

	return log;
}