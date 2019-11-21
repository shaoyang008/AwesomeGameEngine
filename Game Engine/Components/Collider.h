#pragma once
#include "Component.h"
#include "Transform.h"

class Collider : public Component
{
public:
	Collider();
	~Collider();

	void Update();
	void Serialize(json data);

	// Box colliders
	float _posX, _posY, _posZ;
	float _width, _length, _height;
};

