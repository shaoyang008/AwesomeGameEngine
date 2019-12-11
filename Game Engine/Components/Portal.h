/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Porrtal.h
Purpose: Transform to certain level
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

#pragma once
#include "Component.h"

class Portal : public Component
{
public:
	Portal();
	~Portal();

	void Update();
	void Serialize(json);
	void Initialize();
	void HandleEvent(Event*);

private:
	bool _random;
	int _rangeX, _rangeY;
	int _moduloX, _moduloY;
};

