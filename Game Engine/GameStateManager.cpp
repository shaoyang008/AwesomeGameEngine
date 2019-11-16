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
#include "Events/PauseResume.h"

GameStateManager::GameStateManager(): _inputManager(new InputManager), _framerateManager(new FramerateManager(60)), _resourceManager(new ResourceManager),
_gameObjectManager(new GameObjectManager), _physicsManager(new PhysicsManager), _collisionManager(new CollisionManager), _eventManager(new EventManager),
_level(1), _state(STATE::INIT), _gameStates()
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
	delete _gameObjectManager;
	delete _physicsManager;
	delete _collisionManager;
	delete _eventManager;

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
	_gameObjectManager->Initialize();

	// Event subscribtion
	_eventManager->SubscribeEvent(EVENT_TYPE::DELAY_MOVE, *(_gameObjectManager->_tagObjects.FindValueByKey("Enemy1")));
	_eventManager->SubscribeEvent(EVENT_TYPE::DELAY_MOVE, *(_gameObjectManager->_tagObjects.FindValueByKey("Enemy2")));

	_state = STATE::LOOP;
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
		if (s && t) { SDL_BlitSurface(s->_surface, NULL, _windowSurface, t->offset); }
	}
	SDL_UpdateWindowSurface(_window);
	

	// Update physics
	_physicsManager->PhysicsUpdate();

	// Controller event
	_inputManager->UpdateStates();
	if (_inputManager->KeyTriggered(SDL_SCANCODE_P)) {
		Event * e = new PauseResume;
		_eventManager->Enque(e);
	}
	else if (_inputManager->KeyTriggered(SDL_SCANCODE_M)) {
		Event * e = new DelayMove;
		_eventManager->Enque(e);
	}

	for (int i = 0; i < _gameObjectManager->_objects.size(); ++i) {
		Controller * ctrl = dynamic_cast<Controller*>(_gameObjectManager->_objects[i]->GetComponent(COMPONENT_TYPE::CONTROLLER));
		if (ctrl) ctrl->TriggerEvent();
	}

	// Collision detect
	_collisionManager->PlayerCollision("Player");
	_collisionManager->ResolveCollisions();

	// Event queue
	_eventManager->ResolveEvents();

	// Update all game objects
	_gameObjectManager->Update();
	
	// update frame end time
	_framerateManager->FrameEnd();
	return true;
}

void GameStateManager::RunGame()
{
	(this->*(_gameStates[_state]))();
}
