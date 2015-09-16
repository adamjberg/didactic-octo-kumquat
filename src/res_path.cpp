#include "res_path.h"

#include <SDL.h>

std::string getResourcePath( const std::string &subDir ){
#ifdef _WIN32
	const char PATH_SEP = '\\';
#else
	const char PATH_SEP = '/';
#endif
	static std::string baseRes;
	if( baseRes.empty() ){
		char *basePath = SDL_GetBasePath();
		baseRes = basePath;
		SDL_free( basePath );

		size_t pos = baseRes.rfind( "build" );
		baseRes = baseRes.substr( 0, pos ) + "res" + PATH_SEP;
	}
	return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
}