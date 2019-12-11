/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: ToggleAttack.cpp
Purpose: Switch on and off player to attack state
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

#include "ToggleAttack.h"



ToggleAttack::ToggleAttack(int sp): Event(EVENT_TYPE::TOGGLE_ATTACK), _atkType(sp)
{
}


ToggleAttack::~ToggleAttack()
{
}
