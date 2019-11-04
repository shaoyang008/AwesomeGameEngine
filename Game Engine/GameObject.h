/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: GameObject.h
Purpose: Empty game objects holding different components
Language: C
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 10/19/2019

---------------------------------------------------------*/

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