#pragma once

#include <vector>
#include <string>
#include "Components/Component.h"

class GameObject {
public:
	GameObject();
	GameObject(std::string);
	~GameObject();

	void Update();

	Component * GetComponent(COMPONENT_TYPE type);
	bool AddComponent(Component * c);

	std::string GetTag() { return _tag; }
	void SetTag(std::string tag) { _tag = tag; }

	std::vector<Component*> _components;

private:
	std::string _tag;
	bool _active;
};