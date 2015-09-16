#include "utils/File.h"

#include <fstream>
#include <sstream>

std::string readFile( std::string filepath )
{
	std::ifstream file( filepath );
	std::stringstream buffer;
	buffer << file.rdbuf();

	std::string ret = buffer.str();

	return ret;
}