#pragma once
#include "Component.h"

class Portal : public Component
{
public:
	Portal();
	~Portal();

	void Update();
	void Serialize(json);
	void Initialize();
	void HandleEvent(Event*);

private:
	bool _random;
	int _rangeX, _rangeY;
	int _moduloX, _moduloY;
};

