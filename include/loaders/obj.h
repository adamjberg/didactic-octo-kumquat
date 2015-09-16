#pragma once

#include <string>
#include <vector>

#include "GL.h"

bool loadObj( std::string filepath, std::vector < glm::vec3 > & out_vertices, std::vector < glm::vec2 > & out_uvs, std::vector < glm::vec3 > & out_normals, std::vector < GLuint > & indices );