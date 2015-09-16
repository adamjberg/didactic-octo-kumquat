#pragma once

#include <SDL.h>

class UIRenderer
{
public:
	UIRenderer( SDL_Window *window );
	~UIRenderer();

	void render();

	SDL_Renderer *sdlRenderer;
};