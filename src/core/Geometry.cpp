#include "core/Geometry.h"

#include "res_path.h"

#include "loaders/Obj.h"

Geometry::Geometry( std::string filename )
{
	std::string objPath = getResourcePath( "obj" );

	std::vector< glm::vec3 >vertices;
	std::vector<GLuint> indices;
	std::vector< glm::vec2 > uvs;
	std::vector< glm::vec3 > normals;
	loadObj( objPath + filename, vertices, uvs, normals, indices );
	init( vertices, uvs, normals, indices );
}

Geometry::Geometry( std::vector<glm::vec3> &vertices, std::vector<glm::vec2> &uvs, std::vector<glm::vec3> &normals, std::vector<GLuint> &indices )
{
	init( vertices, uvs, normals, indices );
}

void Geometry::init( std::vector<glm::vec3> &vertices, std::vector<glm::vec2> &uvs, std::vector<glm::vec3> &normals, std::vector<GLuint> &indices )
{
	glGenVertexArrays( 1, &VAO );
	glBindVertexArray( VAO );

	GLuint buffer;

	glGenBuffers( 1, &buffer );
	glEnableVertexAttribArray( 0 );
	glBindBuffer( GL_ARRAY_BUFFER, buffer );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, NULL );
	glBufferData( GL_ARRAY_BUFFER, vertices.size() * sizeof( glm::vec3 ), &vertices[ 0 ], GL_STATIC_DRAW );

	glGenBuffers( 1, &buffer );
	glEnableVertexAttribArray( 1 );
	glBindBuffer( GL_ARRAY_BUFFER, buffer );
	glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, NULL );
	glBufferData( GL_ARRAY_BUFFER, uvs.size() * sizeof( glm::vec2 ), &uvs[ 0 ], GL_STATIC_DRAW );

	glGenBuffers( 1, &buffer );
	glEnableVertexAttribArray( 2 );
	glBindBuffer( GL_ARRAY_BUFFER, buffer );
	glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 0, NULL );
	glBufferData( GL_ARRAY_BUFFER, normals.size() * sizeof( glm::vec3 ), &normals[ 0 ], GL_STATIC_DRAW );

	glGenBuffers( 1, &buffer );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, buffer );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof( GLuint ), &indices[ 0 ], GL_STATIC_DRAW );

	glBindVertexArray( -1 );

	size = indices.size();
}