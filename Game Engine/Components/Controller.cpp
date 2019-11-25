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
#include "../Events/ToggleAttack.h"

extern GameStateManager *pMgr;

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
	_speed = data["Speed"].get<float>();
	_accelForce = data["Force"].get<float>();
}

void Controller::TriggerEvent()
{
	Transform * transform = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));
	RigidBody* body = dynamic_cast<RigidBody*>(_owner->GetComponent(COMPONENT_TYPE::RIGID_BODY));
	if (!transform) return;
	
	if (pMgr->_inputManager->KeyPressed(SDL_SCANCODE_UP)) {
		body->_vel = _speed;
	}
	else if (pMgr->_inputManager->KeyPressed(SDL_SCANCODE_DOWN)) {
		body->_vel = -1 * _speed;
	}
	else if (pMgr->_inputManager->KeyReleased(SDL_SCANCODE_UP) || pMgr->_inputManager->KeyReleased(SDL_SCANCODE_DOWN)) {
		body->_vel = 0;
	}

	if (pMgr->_inputManager->KeyPressed(SDL_SCANCODE_LEFT)) {
		transform->_rotateZ += 5;
	}
	else if (pMgr->_inputManager->KeyPressed(SDL_SCANCODE_RIGHT)) {
		transform->_rotateZ -= 5;
	}

	if (pMgr->_inputManager->KeyTriggered(SDL_SCANCODE_SPACE)) {
		Collider * collider = dynamic_cast<Collider*>(_owner->GetComponent(COMPONENT_TYPE::COLLIDER));
		collider->_posZ = 0.1;

		body->_forceZ += _accelForce;
	}

	if (pMgr->_inputManager->KeyTriggered(SDL_SCANCODE_A)) {
		Event * e = new ToggleAttack(true);
		pMgr->_eventManager->Enque(e);
	}
	else if (pMgr->_inputManager->KeyReleased(SDL_SCANCODE_A)) {
		Event * e = new ToggleAttack(false);
		pMgr->_eventManager->Enque(e);
	}
}

void Controller::HandleEvent(Event *e) 
{
}