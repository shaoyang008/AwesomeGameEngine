/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: HealthBar.h
Purpose: Health information of objects
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

#pragma once
#include "Component.h"

class HealthBar : public Component
{
public:
	HealthBar();
	~HealthBar();

	void Update();
	void Initialize();
	void Serialize(json);
	void HandleEvent(Event *);

	int _health;
	std::vector<GameObject*> _hearts;

	int _posX, _posY;
};


