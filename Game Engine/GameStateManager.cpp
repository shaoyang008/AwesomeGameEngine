/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: GameStateManager.cpp
Purpose: Details of different stages of game loops
Language: C
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 10/18/2019

---------------------------------------------------------*/

#include "GameStateManager.h"

GameStateManager::GameStateManager(): _inputManager(new InputManager), _framerateManager(new FramerateManager(60)), _resourceManager(new ResourceManager),
_gameObjectManager(new GameObjectManager), _physicsManager(new PhysicsManager), _level(1), _state(STATE::INIT), _gameStates()
{
	_gameStates[STATE::INIT] = &GameStateManager::Init;
	_gameStates[STATE::LOOP] = &GameStateManager::Loop;
}

GameStateManager::~GameStateManager()
{
	// Delete all managers
	delete _inputManager;
	delete _framerateManager;
	delete _resourceManager;

	std::cout << _gameObjectManager->_objects.size() << " objects." << std::endl;
	for (int i = 0; i < _gameObjectManager->_objects.size(); ++i) {
		std::cout << _gameObjectManager->_objects[i]->_components.size() << std::endl;
	}
	delete _gameObjectManager;

	// Destroy SDL window
	SDL_FreeSurface(_windowSurface);
	SDL_DestroyWindow(_window);
}

void GameStateManager::SetWindow(SDL_Window * window) {
	_window = window;
	_windowSurface = SDL_GetWindowSurface(_window);
}

bool GameStateManager::Load()
{
	return true;
}

bool GameStateManager::Init()
{
	std::string lv = "Level_";
	lv += ('0' + _level);
	_gameObjectManager->LoadLevel(lv);

	_state = STATE::LOOP;
	std::cout << "Init finished. Object count: " << _gameObjectManager->_objects.size() << std::endl;
	*(_gameObjectManager->_objects[0]);
	return true;
}

bool GameStateManager::Loop()
{
	// Record frame start time
	_framerateManager->FrameStart();

	// Draw Background
	for (int i = 0; i < _gameObjectManager->_objects.size(); ++i) {
		Sprite    * s = dynamic_cast<Sprite*>(_gameObjectManager->_objects[i]->GetComponent(COMPONENT_TYPE::SPRITE));
		Transform * t = dynamic_cast<Transform*>(_gameObjectManager->_objects[i]->GetComponent(COMPONENT_TYPE::TRANSFORM));
		if (s && t) { SDL_BlitSurface(s->pSurface, NULL, _windowSurface, t->offset); }
	}
	SDL_UpdateWindowSurface(_window);
	

	// Controller event
	for (int i = 0; i < _gameObjectManager->_objects.size(); ++i) {
		Controller * ctrl = dynamic_cast<Controller*>(_gameObjectManager->_objects[i]->GetComponent(COMPONENT_TYPE::CONTROLLER));
		if(ctrl) ctrl->TriggerEvent();
	}

	// Update physics
	_physicsManager->PhysicsUpdate();

	// Update all game objects
	_gameObjectManager->Update();

	_inputManager->UpdateStates();
	if (_inputManager->KeyPressed(SDL_SCANCODE_Q)) {
		return false;
	}
	
	// update frame end time
	_framerateManager->FrameEnd();
	return true;
}

void GameStateManager::RunGame()
{
	(this->*(_gameStates[_state]))();
}
