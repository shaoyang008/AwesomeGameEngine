#pragma once
#include "Component.h"

class Light : public Component
{
public:
	Light();
	~Light();

	void Update();
	void Serialize(json);

	float _ambient[3];
	float _light[3];
	float _lightPos[3];
	float _angle;
};

