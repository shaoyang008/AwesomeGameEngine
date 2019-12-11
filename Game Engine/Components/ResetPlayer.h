/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: ResetPlayer.h
Purpose: Physic behaviors of objects
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

#pragma once
#include "Component.h"
#include "Transform.h"
#include "RigidBody.h"
#include "../GameObject.h"
#include "../Events/OnCollision.h"

class ResetPlayer : public Component
{
public:
	ResetPlayer();
	~ResetPlayer();

	void Update();
	void Serialize(json);
	void Initialize();
	void HandleEvent(Event *);

private:
	float _posX, _posY;
};

