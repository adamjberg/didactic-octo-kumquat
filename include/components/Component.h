#pragma once

class Object3D;

class Component
{
public:
	Component() {};
	virtual void update() = 0;

	Object3D *object;
};