/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Porrtal.cpp
Purpose: Transform to certain level
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

#include "Portal.h"
#include "Transform.h"
#include "../GameStateManager.h"

#define ROTATE_SPEED 60

extern GameStateManager * pMgr;

Portal::Portal(): Component(COMPONENT_TYPE::PORTAL), _random(false)
{
}


Portal::~Portal()
{
}

void Portal::Update()
{
	Transform * transform = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));
	transform->_rotateZ += ROTATE_SPEED * pMgr->_framerateManager->_frameTime / 1000.0f;
}

void Portal::Serialize(json data)
{
	_random = data["Random"].get<int>();

	if (_random) {
		_rangeX = data["RangeX"].get<int>();
		_rangeY = data["RangeY"].get<int>();

		_moduloX = data["ModuloX"].get<int>();
		_moduloY = data["ModuloY"].get<int>();
	}
}

void Portal::Initialize()
{
	if (_random) {
		Transform * transform = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));
		transform->_translateX = rand() % _moduloX + _rangeX;
		transform->_translateY = rand() % _moduloY + _rangeX;
	}
}

void Portal::HandleEvent(Event * e)
{
	if (e->GetType() == EVENT_TYPE::ON_COLLISION) {
		OnCollision * on_c = dynamic_cast<OnCollision*>(e);
		if (on_c->_target && on_c->_target->GetType() == "player") {
			pMgr->ProcceedLevel();
		}
	}
}
