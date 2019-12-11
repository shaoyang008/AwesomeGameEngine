/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: PhysicsManager.cpp
Purpose: Update physic behaviors
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

#include "PhysicsManager.h"
#include "GameStateManager.h"

extern GameStateManager *pMgr;


PhysicsManager::PhysicsManager()
{
}


PhysicsManager::~PhysicsManager()
{
}

void PhysicsManager::PhysicsUpdate()
{
	for (int i = 0; i < pMgr->_gameObjectManager->_objects.size(); ++i) {
		Component * body = pMgr->_gameObjectManager->_objects[i]->GetComponent(COMPONENT_TYPE::RIGID_BODY);
		if (body) {
			dynamic_cast<RigidBody*>(body)->Integrate(GLOBAL_GRAVITY, pMgr->_framerateManager->_frameTime/1000.0f);
		}
	}
}
