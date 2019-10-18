/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: InputManager.cpp
Purpose: Input events of keyboard
Language: C
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 10/14/2019

---------------------------------------------------------*/

#include "InputManager.h"
#include "SDL_keyboard.h"

InputManager::InputManager() { }

InputManager::~InputManager() { }

void InputManager::update_state()
{
	const Uint8* new_keyboard_states = SDL_GetKeyboardState(NULL);
	if (!new_keyboard_states) return;
	
	std::memcpy(previous_keyboard_states, current_keyboard_states, MAX_STATE_LENGTH);
	std::memcpy(current_keyboard_states, new_keyboard_states, MAX_STATE_LENGTH);
}

bool InputManager::key_pressed(int input_key) // get key scan from sdl
{
	// check key dowm
	return current_keyboard_states[input_key];
}
bool InputManager::key_triggered(int input_key)
{
	if (!previous_keyboard_states) return false;
	// check previous up and current down
	else return (current_keyboard_states[input_key] && !previous_keyboard_states[input_key]);
}
bool InputManager::key_released(int input_key)
{
	if (!previous_keyboard_states) return false;
	// check previous down and current up
	else return (!current_keyboard_states[input_key] && previous_keyboard_states[input_key]);
}