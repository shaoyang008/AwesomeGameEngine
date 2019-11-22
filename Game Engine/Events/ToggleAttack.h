#pragma once
#include "Event.h"

class ToggleAttack : public Event
{
public:
	ToggleAttack(bool);
	~ToggleAttack();

	bool _toggle;
};

