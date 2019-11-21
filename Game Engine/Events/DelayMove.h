#pragma once
#include "Event.h"

#define DELAY_TIME 2.0f

class DelayMove : public Event
{
public:
	DelayMove();
	~DelayMove();

	bool ShouldTrigger();

	float _elapsedTime;
	bool  _queued;
};

