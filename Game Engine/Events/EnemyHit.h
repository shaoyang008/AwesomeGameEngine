#pragma once
#include "Event.h"

class EnemyHit : public Event
{
public:
	EnemyHit();
	EnemyHit(bool);
	~EnemyHit();

	bool _specialAtk;
};

