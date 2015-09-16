#include "renderers/opengl/GLState.h"

GLState::GLState()
{
	initAttributes();
}

void GLState::initAttributes()
{
	for( GLuint &attribute : newAttributes )
	{
		attribute = 0;
	}
}

void GLState::enableAttribute( GLuint attribute )
{
	newAttributes[ attribute ] = 1;
	glEnableVertexAttribArray( attribute );
	enabledAttributes[ attribute ] = 1;
}

void GLState::disableUnusedAttributes()
{
	for( GLuint i = 0; i < NUM_ATTRIBUTES; i++ )
	{
		if( enabledAttributes[ i ] != newAttributes[ i ] )
		{
			glDisableVertexAttribArray( i );
			enabledAttributes[ i ] = 0;
		}
	}
}

void GLState::setBlending()
{
	// TODO: Add enums for blending types 
}

void GLState::setDepthTest( GLboolean depthTest )
{
	if( depthTest )
	{
		glEnable( GL_DEPTH_TEST );
	}
	else
	{
		glDisable( GL_DEPTH_TEST );
	}
}

void GLState::setDepthWrite( GLboolean depthWrite )
{
	glDepthMask( depthWrite );
}

void GLState::setColorWrite( GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha )
{
	glColorMask( red, green, blue, alpha );
}

void GLState::setDoubleSided( GLboolean doubleSided )
{
	if( doubleSided )
	{
		glEnable( GL_CULL_FACE );
	}
	else
	{
		glDisable( GL_CULL_FACE );
	}
}

void GLState::setFlipSided( GLboolean flipSided )
{
	if( flipSided )
	{
		glFrontFace( GL_CW );
	}
	else
	{
		glFrontFace( GL_CCW );
	}
}

void GLState::setLineWidth( GLfloat width )
{
	glLineWidth( width );
}

void GLState::setPolygonOffset( GLboolean polygonOffset, GLfloat factor, GLfloat units )
{
	if( polygonOffset )
	{
		glEnable( GL_POLYGON_OFFSET_FILL );
		glPolygonOffset( factor, units );
	}
	else
	{
		glDisable( GL_POLYGON_OFFSET_FILL );
	}
}

void GLState::reset()
{
	for( GLuint &attribute : enabledAttributes )
	{
		attribute = 0;
	}
}