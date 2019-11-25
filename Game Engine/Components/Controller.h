/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Controller.h
Purpose: Allow to control objects with arrow keys
Language: C
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 10/19/2019

---------------------------------------------------------*/

#pragma once
#include "Component.h"
#include "Transform.h"
#include "../GameObject.h"
#include <SDL_scancode.h>

class Controller : public Component
{
public:
	Controller();
	~Controller();

	void Update();
	void Serialize(json data);
	void HandleEvent(Event *e);

	void TriggerEvent();

	float _speed, _accelForce;
};
