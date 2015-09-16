#pragma once

#include <algorithm>
#include <functional>

#include "signals/Signal.h"

class Tween
{
public:
	typedef std::function<float( float )> easing_function;
	typedef std::function<void( float )> callback_function;

	Tween( float &value, float from, float to, int duration, easing_function easing, callback_function onCompleteFunction = nullptr, callback_function onUpdateFunction = nullptr );
	float update( int dt );

	float &value;
	float from;
	float to;
	int duration;
	easing_function easing;
	Signal<float> onComplete;
	Signal<float> onUpdate;

	int position;
};

