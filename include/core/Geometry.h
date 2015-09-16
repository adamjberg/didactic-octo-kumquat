#pragma once

#include <vector>

#include "GL.h"

class Geometry
{
public:
	Geometry( std::string filename );
	Geometry( std::vector<glm::vec3> &vertices, std::vector<glm::vec2> &uvs, std::vector<glm::vec3> &normals, std::vector<GLuint> &indices );

	void init( std::vector<glm::vec3> &vertices, std::vector<glm::vec2> &uvs, std::vector<glm::vec3> &normals, std::vector<GLuint> &indices );

	GLuint VAO;
	GLuint size;
};