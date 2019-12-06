#pragma once
#include "Event.h"

class ToggleAttack : public Event
{
public:
	ToggleAttack(int);
	~ToggleAttack();

	/*
	0: normal atk
	1: sp atk on
	2: sp atk off
	*/
	int _atkType;
};

