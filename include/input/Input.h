#pragma once

#include <map>

#include "glm/glm.hpp"

#include "core/SDLEventController.h"

#include "signals/Signal.h"

enum CustomButton {
	MOVE_FORWARD,
	MOVE_BACKWARDS,
	STRAFE_LEFT,
	STRAFE_RIGHT,
	NUM_CUSTOM_BUTTONS
};

class Input
{
public:
	Input( SDLEventController &sdlEventController );

	void addKeyToCustomButton( SDL_Scancode scanCode, CustomButton customButton );
	void addControllerToCustomButton( SDL_GameControllerButton button, CustomButton customButton );
	void addMouseButtonToCustomButton( int mouseButton, CustomButton customButton );

	bool isKeyDown( SDL_Scancode scanCode );

	void onKeyUp( SDL_Scancode scanCode );
	void onKeyDown( SDL_Scancode scanCode );
	void checkKeyToCustomMap( SDL_Scancode scanCode, bool isDown );

	bool isControllerButtonUp( SDL_GameControllerButton button );
	bool isControllerButtonDown( SDL_GameControllerButton button );

	void onControllerButtonDown( SDL_GameControllerButton button );
	void onControllerButtonUp( SDL_GameControllerButton button );

	void checkControllerToCustomMap( SDL_GameControllerButton button, bool isDown );

	bool isMouseButtonDown( int mouseButton );

	void onMouseMoved( int xPos, int yPos, int xRel, int yRel );
	void onMouseButtonDown( int mouseButton );
	void onMouseButtonUp( int mouseButton );

	void checkMouseButtonToCustomMap( int mouseButton, bool isDown );

	void fireButtonDown( CustomButton button );
	void fireButtonUp( CustomButton button );

	bool isButtonDown( CustomButton button );

	bool customButtons[ NUM_CUSTOM_BUTTONS ];
	bool controllerButtons[ SDL_CONTROLLER_BUTTON_MAX ];
	bool mouseButtons[ SDL_BUTTON_X2 ];
	bool keys[ SDL_NUM_SCANCODES ];

	std::map<SDL_Scancode, CustomButton> keyToCustomButtonMap;
	std::map<SDL_GameControllerButton, CustomButton> controllerToButtonMap;
	std::map<int, CustomButton> mouseButtonToCustomButtonMap;

	Signal<CustomButton> onButtonDown;
	Signal<CustomButton> onButtonUp;

	Signal<int, int> onMouseMove;

	glm::vec2 mousePosition;
};