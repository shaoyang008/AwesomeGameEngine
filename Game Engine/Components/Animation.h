#pragma once
#include "Component.h"
#include <vector>

#include "../ObjectModel.h"

class Animation : public Component
{
public:
	Animation();
	~Animation();

	void Initialize();
	void Update();
	void Serialize(json);

	void HandleEvent(Event*);

	bool Load(std::string);

	ObjectModel * _original;
	ObjectModel * _animation;
	// std::vector<ObjectModel*> _models;
};

