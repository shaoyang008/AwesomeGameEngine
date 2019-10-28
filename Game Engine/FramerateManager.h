/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: FramerateManager.h
Purpose: Keep game loop at a stable frame rate. Also record frame time.
Language: C
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 10/14/2019

---------------------------------------------------------*/

#pragma once

class FramerateManager {
public:
	FramerateManager(int);
	~FramerateManager();

	void FrameStart();
	void FrameEnd();

	float frame_time;

private:
	const int max_framerate;
	float tick_per_frame;
	float tick_start;
	float tick_end;
};