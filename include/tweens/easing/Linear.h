#pragma once

#include "tweens/easing/Symmetric.h"

namespace easing
{
	float linear_func( float t );

	typedef easing::Symmetric<linear_func> linear;
}