/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Patrol.h
Purpose: Let objects patrol in given speed and time
Language: C
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 10/27/2019

---------------------------------------------------------*/

#include "Patrol.h"
#include "../GameStateManager.h"

extern GameStateManager *pMgr;

Patrol::Patrol(): Component(COMPONENT_TYPE::PATROL), _speedX(0.0), _speedY(0.0), _direction(true), _maxTime(1000.0), _time(0.0)
{
}


Patrol::~Patrol()
{
}

void Patrol::Update()
{
	Transform * t = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));
	if (_time > _maxTime) {
		_direction = !_direction;
		_time = 0;
	}
	else {
		if (_direction) {
			t->_translateX += _speedX;
			t->_translateY += _speedY;
		}
		else {
			t->_translateX -= _speedX;
			t->_translateY -= _speedY;
		}
		_time += pMgr->_framerateManager->_frameTime;
	}
}

void Patrol::Serialize(json data)
{
	_speedX = std::stof(data["SpeedX"].get<std::string>());
	_speedY = std::stof(data["SpeedY"].get<std::string>());
	_time = std::stof(data["Time"].get<std::string>());
}

void Patrol::HandleEvent(Event *e)
{
	if (e->GetType() == EVENT_TYPE::PAUSE_RESUME) {
		_active = !_active;
	}
}
