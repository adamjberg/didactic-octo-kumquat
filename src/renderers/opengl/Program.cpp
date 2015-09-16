#include "renderers/opengl/Program.h"

#include <iostream>

#include "renderers/opengl/Shader.h"

Program::Program( std::string vertexShaderFilename, std::string fragmentShaderFilename )
{
	id = glCreateProgram();

	Shader vertexShader = Shader( GL_VERTEX_SHADER, vertexShaderFilename );
	Shader fragmentShader = Shader( GL_FRAGMENT_SHADER, fragmentShaderFilename );

	glAttachShader( id, vertexShader.id );
	glAttachShader( id, fragmentShader.id );

	glLinkProgram( id );

	glGetProgramiv( id, GL_LINK_STATUS, &linked );

	int infoLogLength = 0;
	int maxLength = infoLogLength;

	glGetProgramiv( id, GL_INFO_LOG_LENGTH, &maxLength );
	log.resize( maxLength );

	glGetProgramInfoLog( id, maxLength, &infoLogLength, &log[ 0 ] );
	std::cout << log;

	glDeleteShader( vertexShader.id );
	glDeleteShader( fragmentShader.id );

	addUniform( new GLUniform( "modelMatrix", MATRIX4x4 ) );
	addUniform( new GLUniform( "viewMatrix", MATRIX4x4 ) );
	addUniform( new GLUniform( "modelViewMatrix", MATRIX4x4 ) );
	addUniform( new GLUniform( "modelViewProjectionMatrix", MATRIX4x4 ) );
	addUniform( new GLUniform( "projectionMatrix", MATRIX4x4 ) );
	addUniform( new GLUniform( "cameraPosition", VECTOR3 ) );
	addUniform( new GLUniform( "tex", TEXTURE ) );
}

Program::~Program()
{
	for( std::pair<std::string, GLUniform *> kv : uniforms )
	{
		delete kv.second;
	}
}

void Program::addUniform( GLUniform *uniform )
{
	glUseProgram( id );

	uniform->location = glGetUniformLocation( id, uniform->name.c_str() );
	uniforms[uniform->name] = uniform;
}

GLUniform* Program::getUniform( std::string name )
{
	return uniforms[ name ];
}