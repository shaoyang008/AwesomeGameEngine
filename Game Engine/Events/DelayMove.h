/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: DelayMove.h
Purpose: Move after a delay time
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

#pragma once
#include "Event.h"

#define DELAY_TIME 2.0f

class DelayMove : public Event
{
public:
	DelayMove();
	~DelayMove();

	bool ShouldTrigger();

	float _elapsedTime;
	bool  _queued;
};

