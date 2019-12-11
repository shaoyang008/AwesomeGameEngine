/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Event.h
Purpose: Base type of all events
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

#pragma once
#include <iostream>

enum class EVENT_TYPE {
	ON_COLLISION,
	DELAY_MOVE,
	TOGGLE_ATTACK,
	PLAYER_HIT,
	ENEMY_HIT,
	GAME_OVER,
	GAME_START,
	SLIDE_CONTROL,
	count
};

class Event
{
public:
	Event() {}
	Event(EVENT_TYPE type): _type(type) {}
	virtual ~Event() {}

	virtual bool ShouldTrigger() { return true;  }
	EVENT_TYPE GetType() { return _type; }

private:
	EVENT_TYPE _type;
};

