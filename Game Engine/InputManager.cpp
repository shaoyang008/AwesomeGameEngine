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

InputManager::InputManager(): _mouseLeft(false), _mouseRight(false) { }

InputManager::~InputManager() { }

void InputManager::UpdateStates()
{
	int fetchedNum = 0;
	const Uint8* new_keyboard_states = SDL_GetKeyboardState(&fetchedNum);

	if (fetchedNum > 512) fetchedNum = 512;
	
	std::memcpy(_previousKeyboardStates, _currentKeyboardStates, MAX_STATE_LENGTH * sizeof(Uint8));
	std::memcpy(_currentKeyboardStates, new_keyboard_states, fetchedNum * sizeof(Uint8));

	_prevMouseLeft = _mouseLeft;
	_prevMouseRight = _mouseRight;
}

bool InputManager::KeyPressed(int input_key) // get key scan from sdl
{
	// check key dowm
	return _currentKeyboardStates[input_key];
}
bool InputManager::KeyTriggered(int input_key)
{
	if (!_previousKeyboardStates) return false;
	// check previous up and current down
	else return (_currentKeyboardStates[input_key] && !_previousKeyboardStates[input_key]);
}
bool InputManager::KeyReleased(int input_key)
{
	if (!_previousKeyboardStates) return false;
	// check previous down and current up
	else return (!_currentKeyboardStates[input_key] && _previousKeyboardStates[input_key]);
}

bool InputManager::LeftMouseTriggered()
{
	return (!_prevMouseLeft && _mouseLeft);
}

bool InputManager::LeftMouseReleased()
{
	return (_prevMouseLeft && !_mouseLeft);
}

bool InputManager::RightMouseTriggered()
{
	return (!_prevMouseRight && _mouseRight);
}

bool InputManager::RightMouseReleased()
{
	return (_prevMouseRight && !_mouseRight);
}
