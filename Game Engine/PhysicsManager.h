/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: PhysicsManager.h
Purpose: Update physic behaviors
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

#pragma once

#include "FramerateManager.h"
#include "GameObjectManager.h"

#define GLOBAL_GRAVITY -98.0f

class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager();

	void PhysicsUpdate();
};

