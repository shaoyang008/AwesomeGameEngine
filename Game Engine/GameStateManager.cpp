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
_renderManager(new RenderManager), _level(1), _state(STATE::LOAD), _gameStates()
{
	_gameStates[STATE::LOAD] = &GameStateManager::Load;
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
	delete _renderManager;

	// Destroy SDL window
	SDL_DestroyWindow(_window);
}

void GameStateManager::SetWindow(SDL_Window * window) {
	_window = window;
	_renderManager->Initialize(_window);
}

bool GameStateManager::Load()
{
	_window = SDL_CreateWindow("SDL2 window",		// window title
		SDL_WINDOWPOS_UNDEFINED,					// initial x position
		SDL_WINDOWPOS_UNDEFINED,					// initial y position
		800,										// width, in pixels
		600,										// height, in pixels
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	// Check that the window was successfully made
	if (NULL == _window)
	{
		// In the event that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return false;
	}

	// Setup Manager
	// SetWindow(window);
	_renderManager->Initialize(_window);

	_state = STATE::INIT;
	return true;
}

bool GameStateManager::Init()
{
	std::string lv = "Level_";
	lv += ('0' + _level);

	_gameObjectManager->LoadLevel(lv);
	_gameObjectManager->Initialize();

	_renderManager->SetCamera("Camera");

	_state = STATE::LOOP;
	return true;
}

bool GameStateManager::Loop()
{
	// Record frame start time
	_framerateManager->FrameStart();

	// Input
	_inputManager->UpdateStates();
	for (int i = 0; i < _gameObjectManager->_objects.size(); ++i) {
		Controller * controller = dynamic_cast<Controller*>(_gameObjectManager->_objects[i]->GetComponent(COMPONENT_TYPE::CONTROLLER));
		if (controller) {
			controller->TriggerEvent();
		}
	}

	if (_inputManager->KeyTriggered(SDL_SCANCODE_M)) {
		_eventManager->Enque(new DelayMove);
	}

	// Physics
	_physicsManager->PhysicsUpdate();

	// Collisions
	_collisionManager->CheckCollisions();
	_collisionManager->ResolveCollisions();

	// Resolve Events
	_eventManager->ResolveEvents();

	// Update all game objects
	_gameObjectManager->Update();

	// Draw everything
	_renderManager->Draw();

	// update frame end time
	_framerateManager->FrameEnd();
	return true;
}

void GameStateManager::RunGame()
{
	(this->*(_gameStates[_state]))();
}
