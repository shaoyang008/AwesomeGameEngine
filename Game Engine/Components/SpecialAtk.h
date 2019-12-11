/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: SpecialAtk.h
Purpose: Special attack for player
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

#pragma once
#include "Component.h"
#include "../ObjectModel.h"

class SpecialAtk : public Component
{
public:
	SpecialAtk();
	~SpecialAtk();

	void Update();
	void Serialize(json);
	void HandleEvent(Event *);
	void Initialize();

	bool Load(std::string);

private:
	ObjectModel * _original;
	ObjectModel * _animation;

	bool _toggleAtk;
};

