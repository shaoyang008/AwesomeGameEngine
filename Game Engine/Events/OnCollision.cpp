/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: OnCollision.cpp
Purpose: Object collides with a target
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

#include "OnCollision.h"

OnCollision::OnCollision(GameObject * target) : Event(EVENT_TYPE::ON_COLLISION), _target(target)
{
}

/*
OnCollision::OnCollision(bool ground_collision): Event(EVENT_TYPE::ON_COLLISION), _groundCollision(ground_collision)
{
}
*/

OnCollision::~OnCollision()
{
}
