/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: NormalAtk.h
Purpose: Normal attack for player
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

#pragma once
#include "Component.h"
#include <vector>

#include "../ObjectModel.h"

class NormalAtk : public Component
{
public:
	NormalAtk();
	~NormalAtk();

	void Initialize();
	void Update();
	void Serialize(json);

	void HandleEvent(Event*);

	bool Load(std::string);
	
	bool _isToggled;
	int _atkFrames;

	ObjectModel * _original;
	ObjectModel * _animation;
};

