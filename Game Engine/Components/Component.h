#pragma once
#include <iostream>
#include <string> 

class GameObject;

enum class COMPONENT_TYPE {
	SPRITE,
	TRANSFORM,
	CONTROLLER,
	PATROL,
	Count // Used to track number of types
};

class Component
{
public:
	Component();
	Component(COMPONENT_TYPE);
	virtual ~Component();

	virtual void Update() = 0;
	virtual void Serialize(std::string data) = 0;

	GameObject * pOwner;
	COMPONENT_TYPE GetType() { return _type; }
private:
	COMPONENT_TYPE _type;
};
