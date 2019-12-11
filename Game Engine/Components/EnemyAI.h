/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: EnemyAI.h
Purpose: Define enemy behaviors
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

#pragma once
#include "Component.h"

class EnemyAI : public Component
{
public:
	EnemyAI();
	~EnemyAI();

	void Update();
	void Serialize(json);
	void Initialize();
	void HandleEvent(Event*);

	void Reborn();

private:
	int _state;
	GameObject * _target;
	float _targetX, _targetY;

	int _size, _atkState;
	float *_speeds;
	float *_endpoints;

	int _atkFrames;
};

