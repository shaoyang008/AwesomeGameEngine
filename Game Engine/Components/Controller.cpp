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

#define MOVEMENT_SPEED 0.5f
#define ACCELRATE_FORCE 5000.0f
#define PI 3.14159f

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
	Transform * transform = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));
	if (!transform) return;
	
	if (pMgr->_inputManager->KeyPressed(SDL_SCANCODE_W)) {
		transform->_translateX += MOVEMENT_SPEED * sin(transform->_rotateZ * PI / 180.0f);
		transform->_translateY -= MOVEMENT_SPEED * cos(transform->_rotateZ * PI / 180.0f);
	}
	else if (pMgr->_inputManager->KeyPressed(SDL_SCANCODE_S)) {
		transform->_translateX -= MOVEMENT_SPEED * sin(transform->_rotateZ * PI / 180.0f);
		transform->_translateY += MOVEMENT_SPEED * cos(transform->_rotateZ * PI / 180.0f);
	}
	if (pMgr->_inputManager->KeyPressed(SDL_SCANCODE_A)) {
		transform->_rotateZ += 5;
	}
	else if (pMgr->_inputManager->KeyPressed(SDL_SCANCODE_D)) {
		transform->_rotateZ -= 5;
	}
}

void Controller::HandleEvent(Event *e)
{
	if (e->GetType() == EVENT_TYPE::PAUSE_RESUME) {
		_active = !_active;
	}
}