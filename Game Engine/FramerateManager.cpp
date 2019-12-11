/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: FramerateManager.cpp
Purpose: Keep game loop at a stable frame rate. Also record frame time.
Language: C
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 10/14/2019

---------------------------------------------------------*/

#include "FramerateManager.h"
#include <time.h>

FramerateManager::FramerateManager(int framerate) : _maxFramerate(framerate), _tickStart(0), _tickEnd(0), _frameTime(0), _tickPerFrame(1000.0/framerate) {}

FramerateManager::~FramerateManager() {}

void FramerateManager::FrameStart()
{
	_tickStart = clock();
}

void FramerateManager::FrameEnd()
{
	_tickEnd = clock();
	_frameTime = _tickEnd - _tickStart;
	while (_frameTime < _tickPerFrame) {
		_tickEnd = clock();
		_frameTime = _tickEnd - _tickStart;
	}
	std::cout << "Frame Rate: " << 1000.0f / _frameTime << std::endl;
}