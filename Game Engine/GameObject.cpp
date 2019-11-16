/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: GameObject.cpp
Purpose: Empty game objects holding different components
Language: C
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 10/19/2019

---------------------------------------------------------*/

#include "GameObject.h"

GameObject::GameObject(): _tag(""), _active(true), _type("")
{

}

GameObject::GameObject(std::string type): _tag(""),  _active(true), _type(type)
{

}

GameObject::~GameObject()
{
	ClearComponents();
}

void GameObject::Update() {
	for (int i = 0; i < _components.size(); ++i) {
		if (_components[i]->_active) _components[i]->Update();
	}
}

Component * GameObject::GetComponent(COMPONENT_TYPE type) {
	for (int i = 0; i < _components.size(); ++i) {
		if (_components[i]->GetType() == type) return _components[i];
	}
	return 0;
}

bool GameObject::AddComponent(Component * c) {
	for (int i = 0; i < _components.size(); ++i) {
		if (_components[i]->GetType() == c->GetType()) return false;
	}
	c->_owner = this;
	_components.push_back(c);
	return true;
}

void GameObject::InitComponents() {
	for (int i = 0; i < _components.size(); ++i) {
		_components[i]->Initialize();
	}
}

void GameObject::ClearComponents() {
	for (int i = 0; i < _components.size(); ++i) {
		delete _components[i];
	}
}

void GameObject::ReceiveEvent(Event * e) {
	for (int i = 0; i < _components.size(); ++i) {
		_components[i]->HandleEvent(e);
	}
}