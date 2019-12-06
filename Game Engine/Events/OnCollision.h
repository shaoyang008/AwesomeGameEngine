#pragma once
#include "Event.h"
#include "../GameObject.h"

class OnCollision : public Event
{
public:
	OnCollision(GameObject *);
	// OnCollision(bool ground_collision);
	~OnCollision();

	// bool _groundCollision;
	GameObject * _target;
};

