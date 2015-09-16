#include "core/SDLEventController.h"

SDLEventController::SDLEventController()
{
	events[ SDL_QUIT ] = std::bind( &SDLEventController::onQuitEvent, this );
	events[ SDL_WINDOWEVENT ] = std::bind( &SDLEventController::onWindowEvent, this );
	events[ SDL_KEYDOWN ] = std::bind( &SDLEventController::onKeyDownEvent, this );
	events[ SDL_KEYUP ] = std::bind( &SDLEventController::onKeyUpEvent, this );

	events[ SDL_JOYDEVICEADDED ] = std::bind( &SDLEventController::onDeviceAdded, this );
	events[ SDL_JOYDEVICEREMOVED ] = std::bind( &SDLEventController::onDeviceRemoved, this );

	events[ SDL_CONTROLLERDEVICEADDED ] = std::bind( &SDLEventController::ignore, this );
	events[ SDL_CONTROLLERDEVICEREMOVED ] = std::bind( &SDLEventController::ignore, this );

	events[ SDL_JOYBUTTONDOWN ] = std::bind( &SDLEventController::onControllerButtonDownEvent, this );
	events[ SDL_JOYBUTTONUP ] = std::bind( &SDLEventController::onControllerButtonUpEvent, this );

	events[ SDL_MOUSEMOTION ] = std::bind( &SDLEventController::onMouseMovedEvent, this );
	events[ SDL_MOUSEBUTTONDOWN ] = std::bind( &SDLEventController::onMouseButtonDownEvent, this );
	events[ SDL_MOUSEBUTTONUP ] = std::bind( &SDLEventController::onMouseButtonUpEvent, this );

	events[ SDL_RENDER_TARGETS_RESET ] = std::bind( &SDLEventController::ignore, this );

	windowEvents[ SDL_WINDOWEVENT_RESIZED ] = std::bind( &SDLEventController::onWindowResizedEvent, this );

	for( int i = SDL_FIRSTEVENT; i < SDL_LASTEVENT; i++ )
	{
		if( events.find( i ) == events.end() )
		{
			SDL_EventState( i, SDL_IGNORE );
		}
	}
}

void SDLEventController::update()
{
	SDL_GameControllerUpdate();
	while( SDL_PollEvent( &event ) != 0 )
	{
		events[ event.type ]();
	}
}

void SDLEventController::ignore()
{

}

void SDLEventController::onQuitEvent()
{
	onQuit.dispatch();
}

void SDLEventController::onWindowEvent()
{
	auto eventFunction = windowEvents.find( event.window.event );
	if( eventFunction != windowEvents.end() )
	{
		windowEvents[ event.window.event ]();
	}
}

void SDLEventController::onWindowResizedEvent()
{
	onWindowResized.dispatch( event.window.data1, event.window.data2 );
}

void SDLEventController::onKeyDownEvent()
{
	if( event.key.repeat == false )
	{
		onKeyDown.dispatch( event.key.keysym.scancode );
	}
}

void SDLEventController::onKeyUpEvent()
{
	if( event.key.repeat == false )
	{
		onKeyUp.dispatch( event.key.keysym.scancode );
	}
}

void SDLEventController::onDeviceAdded()
{
	int id = event.jbutton.which;
	if( controllers.find( id ) == controllers.end() )
	{
		SDL_GameController * gameController = SDL_GameControllerOpen( id );
		controllers[ id ] = gameController;
	}
}

void SDLEventController::onDeviceRemoved()
{
	int id = event.jbutton.which;
	if( controllers.find( id ) != controllers.end() )
	{
		SDL_GameControllerClose( controllers[ id ] );
		controllers.erase( id );
	}
}

void SDLEventController::onControllerButtonDownEvent()
{
	onControllerButtonDown.dispatch( ( SDL_GameControllerButton ) event.jbutton.button );
}

void SDLEventController::onControllerButtonUpEvent()
{
	onControllerButtonUp.dispatch( ( SDL_GameControllerButton ) event.cbutton.button );
}

void SDLEventController::onMouseMovedEvent()
{
	onMouseMoved.dispatch( event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel );
}

void SDLEventController::onMouseButtonDownEvent()
{
	onMouseButtonDown.dispatch( event.button.button );
}

void SDLEventController::onMouseButtonUpEvent()
{
	onMouseButtonUp.dispatch( event.button.button );
}