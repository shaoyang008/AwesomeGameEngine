/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Transform.cpp
Purpose: Translate, Rotate, and Scale of an object
Language: C
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 10/19/2019

---------------------------------------------------------*/

#include "Transform.h"
#include "../GameStateManager.h"

extern GameStateManager *pMgr;

Transform::Transform(): Component(COMPONENT_TYPE::TRANSFORM), _posX(0.0), _posY(0.0)
{
	offset = new SDL_Rect;
	Update();
}

Transform::Transform(float x, float y): Component(COMPONENT_TYPE::TRANSFORM), _posX(x), _posY(y)
{
	offset = new SDL_Rect;
	Update();
}


Transform::~Transform()
{
	delete offset;
}

void Transform::Update() 
{
	offset->x = _posX;
	offset->y = _posY;
}

void Transform::Serialize(json data)
{
	
	_posX = std::stof(data["PosX"].get<std::string>());
	_posY = std::stof(data["PosY"].get<std::string>());
}

void Transform::HandleEvent(Event *e) 
{
	if (e->GetType() == EVENT_TYPE::DELAY_MOVE) {
		DelayMove *d = dynamic_cast<DelayMove*>(e);
		if (d->IsTimeUp()) _posX += 20.0f;
		else if(!d->_queued) {
			d->_queued = true;
			DelayMove *d2 = new DelayMove(d->_elapsedTime + pMgr->_framerateManager->_frameTime / 1000.0f);
			pMgr->_eventManager->Enque(d2);
		}
	}
}