/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: DelayMove.cpp
Purpose: Move after a delay time
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

#include "DelayMove.h"
#include "../GameStateManager.h"

extern GameStateManager *pMgr;


DelayMove::DelayMove(): Event(EVENT_TYPE::DELAY_MOVE), _elapsedTime(0.0f), _queued(false)
{
}


DelayMove::~DelayMove()
{
}

bool DelayMove::ShouldTrigger()
{
	if (_elapsedTime > DELAY_TIME) return true;
	else {
		_elapsedTime += pMgr->_framerateManager->_frameTime / 1000.0f;
		return false;
	}
}
