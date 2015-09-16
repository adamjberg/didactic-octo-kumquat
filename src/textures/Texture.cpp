#include "textures/Texture.h"

#include <SDL_image.h>

#include "res_path.h"
#include "utils/File.h"

Texture::Texture( SDL_Surface *surface )
{
	init( surface );
}

Texture::Texture( std::string filename )
{
	std::string texturePath = getResourcePath( "textures" ) + filename;
	init( IMG_Load( texturePath.c_str() ) );
}

Texture::~Texture()
{
	SDL_FreeSurface( surface );

	glDeleteTextures( 1, &id );
}

void Texture::init( SDL_Surface *surface )
{
	this->surface = surface;

	glGenTextures( 1, &id );
}