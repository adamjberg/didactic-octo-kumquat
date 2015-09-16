#pragma once

#include <functional>
#include <map>

#include <SDL.h>

#include "core/Controller.h"
#include "signals/Signal.h"

class SDLEventController : public Controller
{
public:
	SDLEventController();
	void update();

	void ignore();

	void onQuitEvent();
	void onWindowEvent();
	void onDeviceAdded();
	void onDeviceRemoved();
	void onKeyDownEvent();
	void onKeyUpEvent();

	void onControllerButtonDownEvent();
	void onControllerButtonUpEvent();

	void onMouseMovedEvent();
	void onMouseButtonDownEvent();
	void onMouseButtonUpEvent();

	void onWindowResizedEvent();

	SDL_Event event;

	std::map<int, SDL_GameController *> controllers;

	std::map < int, std::function<void()> > events;
	std::map < int, std::function<void()> > windowEvents;

	Signal<> onQuit;
	Signal<int, int> onWindowResized;

	Signal<SDL_Scancode> onKeyDown;
	Signal<SDL_Scancode> onKeyUp;

	Signal<SDL_GameControllerButton> onControllerButtonDown;
	Signal<SDL_GameControllerButton> onControllerButtonUp;

	Signal<int, int, int, int> onMouseMoved;
	Signal<int> onMouseButtonDown;
	Signal<int> onMouseButtonUp;
};