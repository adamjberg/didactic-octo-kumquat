#include "input/Input.h"

Input::Input( SDLEventController &sdlEventController )
{
	for( bool &button : controllerButtons )
	{
		button = false;
	}

	for( bool &button : customButtons )
	{
		button = false;
	}

	for( bool &key : keys )
	{
		key = false;
	}

	for( bool &mouseButton : mouseButtons )
	{
		mouseButton = false;
	}

	struct KeyButtonPair {
		SDL_Scancode sc;
		CustomButton button;
	};
	std::vector< KeyButtonPair > keyButtonPairs = {
		{ SDL_SCANCODE_W, MOVE_FORWARD },
		{ SDL_SCANCODE_A, STRAFE_LEFT },
		{ SDL_SCANCODE_S, MOVE_BACKWARDS },
		{ SDL_SCANCODE_D, STRAFE_RIGHT },
	};

	for( KeyButtonPair keyButtonPair : keyButtonPairs )
	{
		addKeyToCustomButton( keyButtonPair.sc, keyButtonPair.button );
	}

	struct ControllerButtonPair {
		SDL_GameControllerButton controllerButton;
		CustomButton customButton;
	};
	std::vector< ControllerButtonPair > controllerButtonPairs = {
		{ SDL_CONTROLLER_BUTTON_Y, MOVE_FORWARD },
		{ SDL_CONTROLLER_BUTTON_A, STRAFE_LEFT },
		{ SDL_CONTROLLER_BUTTON_B, MOVE_BACKWARDS },
		{ SDL_CONTROLLER_BUTTON_X, STRAFE_RIGHT },
	};

	for( ControllerButtonPair controllerButtonPair : controllerButtonPairs )
	{
		addControllerToCustomButton( controllerButtonPair.controllerButton, controllerButtonPair.customButton );
	}

	struct MouseButtonCustomButtonPair {
		int mouseButton;
		CustomButton customButton;
	};
	std::vector< MouseButtonCustomButtonPair > mouseButtonCustomButtonPairs = {
		{ SDL_BUTTON_LEFT, MOVE_FORWARD },
		{ SDL_BUTTON_RIGHT, MOVE_BACKWARDS },
	};

	for( MouseButtonCustomButtonPair mouseButtonCustomButtonPair : mouseButtonCustomButtonPairs )
	{
		addMouseButtonToCustomButton( mouseButtonCustomButtonPair.mouseButton, mouseButtonCustomButtonPair.customButton );
	}

	sdlEventController.onKeyDown.add( std::bind( &Input::onKeyDown, this, std::placeholders::_1 ) );
	sdlEventController.onKeyUp.add( std::bind( &Input::onKeyUp, this, std::placeholders::_1 ) );

	sdlEventController.onControllerButtonDown.add( std::bind( &Input::onControllerButtonDown, this, std::placeholders::_1 ) );
	sdlEventController.onControllerButtonUp.add( std::bind( &Input::onControllerButtonUp, this, std::placeholders::_1 ) );

	sdlEventController.onMouseMoved.add( std::bind( &Input::onMouseMoved, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4 ) );
	sdlEventController.onMouseButtonDown.add( std::bind( &Input::onMouseButtonDown, this, std::placeholders::_1 ) );
	sdlEventController.onMouseButtonUp.add( std::bind( &Input::onMouseButtonUp, this, std::placeholders::_1 ) );
}

void Input::addKeyToCustomButton( SDL_Scancode scanCode, CustomButton customButton )
{
	keyToCustomButtonMap[ scanCode ] = customButton;
}

void Input::addControllerToCustomButton( SDL_GameControllerButton button, CustomButton customButton )
{
	controllerToButtonMap[ button ] = customButton;
}

void Input::addMouseButtonToCustomButton( int mouseButton, CustomButton customButton )
{
	mouseButtonToCustomButtonMap[ mouseButton ] = customButton;
}

bool Input::isKeyDown( SDL_Scancode scanCode )
{
	return keys[ scanCode ];
}

void Input::onKeyDown( SDL_Scancode scanCode )
{
	keys[ scanCode ] = true;
	checkKeyToCustomMap( scanCode, true );
}

void Input::onKeyUp( SDL_Scancode scanCode )
{
	keys[ scanCode ] = false;
	checkKeyToCustomMap( scanCode, false );
}

void Input::checkKeyToCustomMap( SDL_Scancode scanCode, bool isDown )
{
	if( keyToCustomButtonMap.find( scanCode ) != keyToCustomButtonMap.end() )
	{
		if( isDown )
		{
			fireButtonDown( keyToCustomButtonMap[ scanCode ] );
		}
		else
		{
			fireButtonUp( keyToCustomButtonMap[ scanCode ] );
		}
	}
}

bool Input::isControllerButtonDown( SDL_GameControllerButton button )
{
	return controllerButtons[ button ];
}

void Input::onControllerButtonDown( SDL_GameControllerButton button )
{
	controllerButtons[ button ] = true;
	checkControllerToCustomMap( button, true );
}

void Input::onControllerButtonUp( SDL_GameControllerButton button )
{
	controllerButtons[ button ] = false;
	checkControllerToCustomMap( button, false );
}

void Input::checkControllerToCustomMap( SDL_GameControllerButton button, bool isDown )
{
	if( controllerToButtonMap.find( button ) != controllerToButtonMap.end() )
	{
		if( isDown )
		{
			fireButtonDown( controllerToButtonMap[ button ] );
		}
		else
		{
			fireButtonUp( controllerToButtonMap[ button ] );
		}
	}
}

bool Input::isMouseButtonDown( int mouseButton )
{
	return mouseButtons[ mouseButton ];
}

void Input::onMouseMoved( int xPos, int yPos, int xRel, int yRel )
{
	mousePosition.x = (float) xPos;
	mousePosition.y = (float) yPos;
	onMouseMove.dispatch( xRel, yRel );
}

void Input::onMouseButtonDown( int mouseButton )
{
	mouseButtons[ mouseButton ] = true;
	checkMouseButtonToCustomMap( mouseButton, true );
}

void Input::onMouseButtonUp( int mouseButton )
{
	mouseButtons[ mouseButton ] = false;
	checkMouseButtonToCustomMap( mouseButton, false );
}

void Input::checkMouseButtonToCustomMap( int mouseButton, bool isDown )
{
	if( mouseButtonToCustomButtonMap.find( mouseButton ) != mouseButtonToCustomButtonMap.end() )
	{
		if( isDown )
		{
			fireButtonDown( mouseButtonToCustomButtonMap[ mouseButton ] );
		}
		else
		{
			fireButtonUp( mouseButtonToCustomButtonMap[ mouseButton ] );
		}
	}
}

void Input::fireButtonDown( CustomButton button )
{
	customButtons[ button ] = true;
	onButtonDown.dispatch( button );
}
void Input::fireButtonUp( CustomButton button )
{
	customButtons[ button ] = false;
	onButtonUp.dispatch( button );
}

bool Input::isButtonDown( CustomButton button )
{
	return customButtons[ button ];
}