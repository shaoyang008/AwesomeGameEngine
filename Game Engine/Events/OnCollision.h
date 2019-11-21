#pragma once
#include "Event.h"

class OnCollision : public Event
{
public:
	OnCollision(bool ground_collision = false);
	~OnCollision();

	bool _groundCollision;
};

