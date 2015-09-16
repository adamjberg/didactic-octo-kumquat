#pragma once

#include "input/Input.h"
#include "components/Component.h"
#include "core/Controller.h"

class FPSCamera : public Component
{
public:
	FPSCamera( Input &input );
	void update();
	void mouseMoved(int xRel, int yRel);

	Input *input;
};