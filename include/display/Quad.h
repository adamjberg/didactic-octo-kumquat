#pragma once

#include "glm/glm.hpp"

#include "objects/Mesh.h"

class Quad : public Mesh
{
public:
	Quad(int width, int height, glm::vec3 color);
};