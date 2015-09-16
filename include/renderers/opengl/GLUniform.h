#pragma once

#include <string>

enum UniformType {
	INVALID_TYPE = -1,
	MATRIX4x4,
	VECTOR3,
	VECTOR4,
	TEXTURE,
	NUM_UNIFORM_TYPES
};

class GLUniform
{
public:
	GLUniform( std::string name, UniformType type, void *value = nullptr );

	std::string name;
	void *value;
	UniformType type;
	bool needsUpdate;
	int location;
};