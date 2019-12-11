/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: RigidBody.h
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

class RigidBody : public Component
{
public:
	RigidBody();
	~RigidBody();

	void Update();
	void Serialize(json);

	// Initialize physic values
	void Initialize();
	void HandleEvent(Event *);

	// Add up all forces in dt and apply to objects
	void Integrate(float, float);
	void Stop();

	float _force, _forceZ;
	float _vel, _velZ;
	float _acc, _accZ;

	float _posX, _posY, _posZ;
	float _prevPosX, _prevPosY, _prevPosZ;

private:
	float _mass, _gravityScale;
};

