#pragma once
#include "Component.h"
#include "../GameObject.h"

class BossAI : public Component
{
public:
	BossAI();
	~BossAI();

	void Update();
	void Serialize(json);
	void Initialize();
	void HandleEvent(Event *);

	GameObject * _target;
	int _state, _stateCounter, _spCounter;
};

