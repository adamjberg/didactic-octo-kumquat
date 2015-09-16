#include "display/Quad.h"

Quad::Quad( int width, int height, glm::vec3 color )
{
	Program *program = new Program( "quad.vs", "quad.fs" );
	//material = new Material( program );
	geometry = new Geometry("Quad.obj");
}