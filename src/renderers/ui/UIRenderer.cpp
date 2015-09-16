#include "renderers/ui/UIRenderer.h"

UIRenderer::UIRenderer( SDL_Window *window )
{
	sdlRenderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

	SDL_SetRenderDrawBlendMode( sdlRenderer, SDL_BLENDMODE_ADD );
}

UIRenderer::~UIRenderer()
{
	SDL_DestroyRenderer( sdlRenderer );
}

void UIRenderer::render()
{
	SDL_SetRenderDrawColor( sdlRenderer, 100, 0, 0, 0xff );
	SDL_RenderClear( sdlRenderer );

	SDL_RenderPresent( sdlRenderer );
}