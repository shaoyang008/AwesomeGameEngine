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

Controller::Controller(): Component(COMPONENT_TYPE::CONTROLLER)
{
}


Controller::~Controller()
{
}

void Controller::Update()
{
}

void Controller::Serialize(std::string data)
{
}

void Controller::TriggerEvent()
{
	Transform * t = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));
	if (!t) return;

	if (pMgr->_inputManager->KeyPressed(SDL_SCANCODE_UP)) {
		t->_posY -= MOVEMENT_SPEED;
	}
	else if (pMgr->_inputManager->KeyPressed(SDL_SCANCODE_DOWN)) {
		t->_posY += MOVEMENT_SPEED;
	}
	else if (pMgr->_inputManager->KeyPressed(SDL_SCANCODE_LEFT)) {
		t->_posX -= MOVEMENT_SPEED;
	}
	else if (pMgr->_inputManager->KeyPressed(SDL_SCANCODE_RIGHT)) {
		t->_posX += MOVEMENT_SPEED;
	}
}