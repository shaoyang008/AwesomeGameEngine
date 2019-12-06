#pragma once
#include "Component.h"
#include <vector>

#include "../ObjectModel.h"

class NormalAtk : public Component
{
public:
	NormalAtk();
	~NormalAtk();

	void Initialize();
	void Update();
	void Serialize(json);

	void HandleEvent(Event*);

	bool Load(std::string);
	
	bool _isToggled;
	int _atkFrames;

	ObjectModel * _original;
	ObjectModel * _animation;
};

