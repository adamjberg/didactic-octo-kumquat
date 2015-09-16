#ifndef GLSTATE_H
#define GLSTATE_H

#include "GL.h"

#define NUM_ATTRIBUTES 16

class GLState
{
public:
	GLuint newAttributes[ NUM_ATTRIBUTES ];
	GLuint enabledAttributes[ NUM_ATTRIBUTES ];

	GLState::GLState();
	void initAttributes();
	void enableAttribute( GLuint attribute );
	void disableUnusedAttributes();
	void setBlending();
	void setDepthTest( GLboolean depthTest );
	void setDepthWrite( GLboolean depthWrite );
	void setColorWrite( GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha );
	void setDoubleSided( GLboolean doubleSided );
	void setFlipSided( GLboolean flipSided );
	void setLineWidth( GLfloat width );
	void setPolygonOffset( GLboolean polygonOffset, GLfloat factor, GLfloat units );
	void reset();
};

#endif