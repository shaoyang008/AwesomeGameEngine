#pragma once

#include "FramerateManager.h"
#include "GameObjectManager.h"

#define GLOBAL_GRAVITY 98.0f

class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager();

	void PhysicsUpdate();
};

