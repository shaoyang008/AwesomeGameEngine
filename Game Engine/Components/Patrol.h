#pragma once
#include "Component.h"
#include "Transform.h"
#include "../GameObject.h"

class Patrol: public Component
{
public:
	Patrol();
	~Patrol();

	void Update();
	void Serialize(std::string);

private:
	bool _direction;
	float _speedX, _speedY;
	float _maxTime, _time;
};

