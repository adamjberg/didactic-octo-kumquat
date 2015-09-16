#include "materials/Material.h"

Material::Material( Program *program, Texture *texture ) : program( program ), texture( texture )
{
	uniforms = program->uniforms;

	addUniform( new GLUniform( "tex", TEXTURE, texture ) );
}

void Material::addUniform( GLUniform *uniform )
{
	glUseProgram( program->id );

	uniform->location = glGetUniformLocation( program->id, uniform->name.c_str() );
	uniforms[ uniform->name ] = uniform;
}