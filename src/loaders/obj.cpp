#include "loaders/obj.h"

#include <map>
#include <sstream>

#include "utils/File.h"

struct PackedIndexedVertex
{
	unsigned int vertexIndex, uvIndex, normalIndex;

	bool operator<( const PackedIndexedVertex that ) const{
		return memcmp( ( void* )this, ( void* ) &that, sizeof( PackedIndexedVertex ) ) > 0;
	};
};

bool loadObj( std::string filepath, std::vector < glm::vec3 > & out_vertices, std::vector < glm::vec2 > & out_uvs, std::vector < glm::vec3 > & out_normals, std::vector < GLuint > & out_indices )
{
	std::vector< glm::vec3 > temp_vertices, temp_normals;
	std::vector< glm::vec2 > temp_uvs;

	std::map<PackedIndexedVertex, unsigned int> vertexIndexMap;

	std::string contents = readFile( filepath );
	std::istringstream iss( contents );

	for( std::string line; std::getline( iss, line ); )
	{
		if( line.substr( 0, 2 ) == "v " )
		{
			std::istringstream s( line.substr( 2 ) );
			glm::vec3 v; s >> v.x; s >> v.y; s >> v.z;
			temp_vertices.push_back( v );
		}
		else if( line.substr( 0, 3 ) == "vt " )
		{
			std::istringstream s( line.substr( 3 ) );
			glm::vec2 uv; s >> uv.x; s >> uv.y;
			temp_uvs.push_back( uv );
		}
		else if( line.substr( 0, 3 ) == "vn " )
		{
			std::istringstream s( line.substr( 3 ) );
			glm::vec3 normal; s >> normal.x; s >> normal.y; s >> normal.z;
			temp_normals.push_back( normal );
		}
		else if( line.substr( 0, 2 ) == "f " )
		{
			std::istringstream s( line.substr( 2 ) );
			PackedIndexedVertex vertex;
			char slash;

			for( int i = 0; i < 3; i++ )
			{
				s >> vertex.vertexIndex; s >> slash;
				s >> vertex.uvIndex; s >> slash;
				s >> vertex.normalIndex;
				std::map<PackedIndexedVertex, unsigned int>::iterator vertexIndex = vertexIndexMap.find( vertex );

				if( vertexIndex == vertexIndexMap.end() )
				{
					out_vertices.push_back( temp_vertices[ vertex.vertexIndex - 1 ] );
					out_uvs.push_back( temp_uvs[ vertex.uvIndex - 1 ] );
					out_normals.push_back( temp_normals[ vertex.normalIndex - 1 ] );

					unsigned int newIndex = out_vertices.size() - 1;
					out_indices.push_back( newIndex );
					vertexIndexMap[ vertex ] = newIndex;
				}
				else
				{
					out_indices.push_back( vertexIndex->second );
				}
			}
		}
	}

	return true;
}