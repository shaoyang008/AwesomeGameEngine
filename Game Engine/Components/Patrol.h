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

#pragma once
#include "Component.h"
#include "Transform.h"
#include "../GameObject.h"

class Patrol: public Component
{
public:
	Patrol();
	~Patrol();

	void Update();
	void Serialize(json data);
	void HandleEvent(Event*);

private:
	bool _direction;
	float _speedX, _speedY;
	float _maxTime, _time;
};

