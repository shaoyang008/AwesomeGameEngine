/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: EnemyHit.cpp
Purpose: Enemy got hit
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

#include "EnemyHit.h"



EnemyHit::EnemyHit(): Event(EVENT_TYPE::ENEMY_HIT), _specialAtk(false)
{
}

EnemyHit::EnemyHit(bool special) : Event(EVENT_TYPE::ENEMY_HIT), _specialAtk(special)
{
}


EnemyHit::~EnemyHit()
{
}
