#pragma once
#include "Component.h"

#include <string>

class Follow : public Component
{
public:
	Follow();
	~Follow();

	void Update();
	void Serialize(json);
	void Initialize();

	std::string _followTag;
	GameObject * _followObject;
	float _distanceX, _distanceY;
};

