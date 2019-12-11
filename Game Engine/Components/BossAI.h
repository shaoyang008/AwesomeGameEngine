/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Boss.h
Purpose: Define boss behaviors
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

#pragma once
#include "Component.h"
#include "../GameObject.h"

class BossAI : public Component
{
public:
	BossAI();
	~BossAI();

	void Update();
	void Serialize(json);
	void Initialize();
	void HandleEvent(Event *);

	GameObject * _target;
	int _state, _stateCounter, _spCounter;
};

