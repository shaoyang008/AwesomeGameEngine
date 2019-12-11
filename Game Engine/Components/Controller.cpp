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
#include "../Events/GameOver.h"

extern GameStateManager *pMgr;

#define PLAYER_ROTATE_SPEED 300.0f

Controller::Controller(): Component(COMPONENT_TYPE::CONTROLLER), _mode(0)
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

	if (data["ControlMode"].get<std::string>() == "Keyboard") {
		_mode = 0;
	}
	else if (data["ControlMode"].get<std::string>() == "Mouse") {
		_mode = 1;
	}
	else {
		std::cout << "Unknown control mode. Use default Keyboard mode." << std::endl;
		_mode = 0;
	}
}

void Controller::TriggerEvent()
{
	if (!_active) return;

	Transform * transform = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));
	RigidBody* body = dynamic_cast<RigidBody*>(_owner->GetComponent(COMPONENT_TYPE::RIGID_BODY));
	if (!transform) return;
	
	if (_mode == 0) {
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
			transform->_rotateZ += PLAYER_ROTATE_SPEED * pMgr->_framerateManager->_frameTime / 1000.0f;
		}
		else if (pMgr->_inputManager->KeyPressed(SDL_SCANCODE_RIGHT)) {
			transform->_rotateZ -= PLAYER_ROTATE_SPEED * pMgr->_framerateManager->_frameTime / 1000.0f;
		}

		if (pMgr->_inputManager->KeyTriggered(SDL_SCANCODE_A)) {
			Event * e = new ToggleAttack(0);
			pMgr->_eventManager->Enque(e);
		}
		if (pMgr->_inputManager->KeyTriggered(SDL_SCANCODE_S)) {
			Event * e = new ToggleAttack(1);
			pMgr->_eventManager->Enque(e);
		}
		if (pMgr->_inputManager->KeyReleased(SDL_SCANCODE_S)) {
			Event * e = new ToggleAttack(2);
			pMgr->_eventManager->Enque(e);
		}
	}
	else if (_mode == 1) {
		if (pMgr->_inputManager->KeyPressed(SDL_SCANCODE_W)) {
			body->_vel = _speed;
		}
		else if (pMgr->_inputManager->KeyPressed(SDL_SCANCODE_S)) {
			body->_vel = -1 * _speed;
		}
		else if (pMgr->_inputManager->KeyReleased(SDL_SCANCODE_W) || pMgr->_inputManager->KeyReleased(SDL_SCANCODE_S)) {
			body->_vel = 0;
		}

		if (pMgr->_inputManager->KeyPressed(SDL_SCANCODE_A)) {
			transform->_rotateZ += 5;
		}
		else if (pMgr->_inputManager->KeyPressed(SDL_SCANCODE_D)) {
			transform->_rotateZ -= 5;
		}

		if (pMgr->_inputManager->LeftMouseTriggered()) {
			Event * e = new ToggleAttack(0);
			pMgr->_eventManager->Enque(e);
		}
		if (pMgr->_inputManager->RightMouseTriggered()) {
			Event * e = new ToggleAttack(1);
			pMgr->_eventManager->Enque(e);
		}
		if (pMgr->_inputManager->RightMouseReleased()) {
			Event * e = new ToggleAttack(2);
			pMgr->_eventManager->Enque(e);
		}
	}


	if (pMgr->_inputManager->KeyTriggered(SDL_SCANCODE_SPACE) || pMgr->_inputManager->LeftMouseTriggered()) {
		Collider * collider = dynamic_cast<Collider*>(_owner->GetComponent(COMPONENT_TYPE::COLLIDER));
		collider->_posZ = 0.1f;

		body->_forceZ += _accelForce;
	}
}

void Controller::HandleEvent(Event *e) 
{
	if (e->GetType() == EVENT_TYPE::GAME_OVER) {
		GameOver * go = dynamic_cast<GameOver*>(e);
		if (!go->_victory) {
			_active = false;
		}
	}
}

void Controller::Initialize()
{
	_active = true;
}
