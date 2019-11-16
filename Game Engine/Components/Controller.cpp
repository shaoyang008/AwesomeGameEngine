/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Controller.cpp
Purpose: Allow to control objects with arrow keys
Language: C
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 10/19/2019

---------------------------------------------------------*/

#include "Controller.h"
#include "../GameStateManager.h"

extern GameStateManager *pMgr;

#define MOVEMENT_SPEED 5
#define ACCELRATE_FORCE 5000.0f

Controller::Controller(): Component(COMPONENT_TYPE::CONTROLLER)
{
}


Controller::~Controller()
{
}

void Controller::Update()
{
}

void Controller::Serialize(json data)
{
}

void Controller::TriggerEvent()
{
	Transform * t = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));
	if (!t) return;

	RigidBody * r = dynamic_cast<RigidBody*>(_owner->GetComponent(COMPONENT_TYPE::RIGID_BODY));
	if (!t) return;

	if (pMgr->_inputManager->KeyPressed(SDL_SCANCODE_UP)) {
		r->_forceY -= ACCELRATE_FORCE;
	}
	else if (pMgr->_inputManager->KeyPressed(SDL_SCANCODE_DOWN)) {
		r->_forceY += ACCELRATE_FORCE;
	}
	
	if (pMgr->_inputManager->KeyPressed(SDL_SCANCODE_LEFT)) {
		t->_posX -= MOVEMENT_SPEED;
	}
	else if (pMgr->_inputManager->KeyPressed(SDL_SCANCODE_RIGHT)) {
		t->_posX += MOVEMENT_SPEED;
	}
}

void Controller::HandleEvent(Event *e)
{
	if (e->GetType() == EVENT_TYPE::PAUSE_RESUME) {
		_active = !_active;
	}
}