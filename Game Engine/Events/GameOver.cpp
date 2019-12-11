/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: GameOver.cpp
Purpose: Game over either win or lose
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

#include "GameOver.h"



GameOver::GameOver(): Event(EVENT_TYPE::GAME_OVER), _victory(false)
{
}

GameOver::GameOver(bool victory) : Event(EVENT_TYPE::GAME_OVER), _victory(victory)
{
}

GameOver::~GameOver()
{
}
