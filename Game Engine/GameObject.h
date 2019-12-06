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
#include "Events/Event.h"

class GameObject {
public:
	GameObject();
	GameObject(std::string);
	~GameObject();

	void Update();

	Component * GetComponent(COMPONENT_TYPE);
	bool AddComponent(Component*);
	void InitComponents();
	void ClearComponents();
	void ReceiveEvent(Event *);

	std::string GetTag() const { return _tag; }
	void SetTag(std::string tag) { _tag = tag; }

	std::string GetType() const { return _type; }
	void SetType(std::string type) { _type = type; }

	std::vector<Component*> _components;
	
	void Activate() { _active = true; }
	void Deactivate() { _active = false; }
	bool IsActive() { return _active; }

	/*
	TODO: unique objects will be inherited throughout the
	whole game, not reset while switching through levels
	*/
	void SetUnique() { _unique = true; }
	bool IsUnique() { return _unique; }

private:
	std::string _tag;
	std::string _type;

	bool _active;
	bool _unique;
};