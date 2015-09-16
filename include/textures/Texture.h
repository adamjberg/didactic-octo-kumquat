#pragma once

#include <string>

#include <SDL.h>
#include "GL.h"

class Texture {
public:
	Texture( SDL_Surface *surface );
	Texture( std::string filename );
	~Texture();

	void init( SDL_Surface *surface );

	SDL_Surface *surface;

	GLuint id;

	GLuint magFilter = GL_NEAREST;
	GLuint minFilter = GL_NEAREST;
};