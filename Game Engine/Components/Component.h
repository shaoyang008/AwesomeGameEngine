/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Component.h
Purpose: Base class of components
Language: C
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 10/19/2019

---------------------------------------------------------*/

#pragma once
#include <iostream>
#include <string> 

#include <json.hpp>
using json = nlohmann::json;

class GameObject;

enum class COMPONENT_TYPE {
	SPRITE,
	TRANSFORM,
	CONTROLLER,
	PATROL,
	RIGID_BODY,
	Count // Used to track number of types
};

class Component
{
public:
	Component();
	Component(COMPONENT_TYPE);
	virtual ~Component();
	// virtual Component * clone() = 0;

	virtual void Update() = 0;
	virtual void Serialize(json data) = 0;

	GameObject * _owner;
	COMPONENT_TYPE GetType() { return _type; }
private:
	COMPONENT_TYPE _type;
};
