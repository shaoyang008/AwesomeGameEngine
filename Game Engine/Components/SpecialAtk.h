#pragma once
#include "Component.h"
#include "../ObjectModel.h"

class SpecialAtk : public Component
{
public:
	SpecialAtk();
	~SpecialAtk();

	void Update();
	void Serialize(json);
	void HandleEvent(Event *);
	void Initialize();

	bool Load(std::string);

private:
	ObjectModel * _original;
	ObjectModel * _animation;

	bool _toggleAtk;
};

