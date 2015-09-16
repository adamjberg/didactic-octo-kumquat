#pragma once

#include <SDL.h>

class Window
{
public:
	Window( const char* windowName, int width, int height );
	~Window();

	SDL_Window *sdlWindow;
};