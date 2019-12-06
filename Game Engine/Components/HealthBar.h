#pragma once
#include "Component.h"

class HealthBar : public Component
{
public:
	HealthBar();
	~HealthBar();

	void Update();
	void Initialize();
	void Serialize(json);
	void HandleEvent(Event *);

	int _health;
	std::vector<GameObject*> _hearts;

	int _posX, _posY;
};


