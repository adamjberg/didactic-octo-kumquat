#pragma once

#include <vector>

#include "GL.h"

#include "components/Component.h"
#include "signals/Signal.h"

class Object3D
{
public:
	Object3D();
	virtual ~Object3D();

	void add( Object3D &object );
	void add( Component &component );

	void update();

	virtual void updateMatrix();

	void setPosition( glm::vec3 position );
	void setRotation( glm::vec3 rotation );
	void setScale( glm::vec3 scale );

	bool needsUpdate;

	std::vector<Object3D *> children;
	std::vector<Component *> components;

	glm::mat4 matrix;
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;

	Signal<> onUpdate;
	Signal<> onPositionChanged;
	Signal<> onScaleChanged;
	Signal<> onRotationChanged;
};