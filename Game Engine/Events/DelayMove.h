#pragma once
#include "Event.h"

#define DELAY_TIME 2.0f

class DelayMove : public Event
{
public:
	DelayMove();
	DelayMove(float);
	~DelayMove();

	bool IsTimeUp() { return (_elapsedTime > DELAY_TIME);  }

	float _elapsedTime;
	bool  _queued;
};

