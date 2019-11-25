#pragma once
#include "Event.h"

class OnCollision : public Event
{
public:
	OnCollision();
	OnCollision(bool ground_collision);
	~OnCollision();

	bool _groundCollision;
};

