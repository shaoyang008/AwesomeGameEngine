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

FramerateManager::FramerateManager(int framerate) : max_framerate(framerate), tick_start(0), tick_end(0), frame_time(0), tick_per_frame(1000.0/framerate) {}

FramerateManager::~FramerateManager() {}

void FramerateManager::FrameStart()
{
	tick_start = clock();
}

void FramerateManager::FrameEnd()
{
	tick_end = clock();
	frame_time = tick_end - tick_start;
	while (frame_time < tick_per_frame) {
		tick_end = clock();
		frame_time = tick_end - tick_start;
	}
}