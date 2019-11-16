#pragma once
#include <iostream>

enum class EVENT_TYPE {
	ON_COLLISION,
	DELAY_MOVE,
	PAUSE_RESUME,
	count
};

class Event
{
public:
	Event() {}
	Event(EVENT_TYPE type): _type(type) {}
	virtual ~Event() {}

	EVENT_TYPE GetType() { return _type; }

private:
	EVENT_TYPE _type;
};

