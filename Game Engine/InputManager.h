/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: InputManager.h
Purpose: Input events of keyboard
Language: C
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 10/14/2019

---------------------------------------------------------*/

#pragma once

#include <iostream>

#define MAX_STATE_LENGTH 512

class InputManager {
public:
	InputManager();
	~InputManager();

	void update_state();

	bool key_pressed(int);
	bool key_triggered(int);
	bool key_released(int);

private:
	char current_keyboard_states[MAX_STATE_LENGTH];
	char previous_keyboard_states[MAX_STATE_LENGTH]; // compare to detect trigger and release
};