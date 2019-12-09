#pragma once
#include <iostream>

enum class EVENT_TYPE {
	ON_COLLISION,
	DELAY_MOVE,
	TOGGLE_ATTACK,
	PLAYER_HIT,
	ENEMY_HIT,
	GAME_OVER,
	GAME_START,
	SLIDE_CONTROL,
	count
};

class Event
{
public:
	Event() {}
	Event(EVENT_TYPE type): _type(type) {}
	virtual ~Event() {}

	virtual bool ShouldTrigger() { return true;  }
	EVENT_TYPE GetType() { return _type; }

private:
	EVENT_TYPE _type;
};

