#pragma once
#include "Event.h"

class GameOver : public Event
{
public:
	GameOver();
	GameOver(bool);
	~GameOver();

	bool _victory;
};

