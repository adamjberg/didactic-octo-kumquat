#include "renderers/opengl/GLUniform.h"

GLUniform::GLUniform( std::string name, UniformType type, void *value ) : name( name ), type( type ), value( value )
{
	needsUpdate = true;
	location = -1;
	value = nullptr;
}