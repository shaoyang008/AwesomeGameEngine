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

#define DEFAULT_LEVEL 1

GameStateManager::GameStateManager(): _inputManager(new InputManager), _framerateManager(new FramerateManager(60)), _resourceManager(new ResourceManager),
_gameObjectManager(new GameObjectManager), _physicsManager(new PhysicsManager), _collisionManager(new CollisionManager), _eventManager(new EventManager),
_renderManager(new RenderManager), _level(DEFAULT_LEVEL), _state(STATE::LOAD), _gameStates(), _settingsLoaded(false)
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

void GameStateManager::LoadSettings()
{
	json settings_data = JsonHandle::ReadFile("Levels/Settings.json");
	_gameObjectManager->LoadLevel(settings_data["GameObjects"]);
	/*
	for (int i = 0; i < _gameObjectManager->_objects.size(); ++i) {
		_gameObjectManager->_objects[i]->SetUnique();
	}
	*/

	_renderManager->SetCamera("Viewer");

	// Subscribe events
	_eventManager->ClearSubscribe();
	_eventManager->SubscribeEvent(EVENT_TYPE::PLAYER_HIT, _gameObjectManager->_tagObjects.FindValueByKey("Player"));
	_eventManager->SubscribeEvent(EVENT_TYPE::SLIDE_CONTROL, _gameObjectManager->_tagObjects.FindValueByKey("Story"));

	_settingsLoaded = true;
}

bool GameStateManager::Load()
{
	_window = SDL_CreateWindow("SDL2 window",		// window title
		SDL_WINDOWPOS_UNDEFINED,					// initial x position
		SDL_WINDOWPOS_UNDEFINED,					// initial y position
		800,										// width, in pixels
		600,										// height, in pixels
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	// Check that the window was successfully made
	if (NULL == _window)
	{
		// In the event that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return false;
	}

	// Setup Manager
	_renderManager->Initialize(_window);

	_state = STATE::INIT;
	return true;
}

bool GameStateManager::Init()
{
	// Load basic settings, including unique objects
	if(!_settingsLoaded) LoadSettings();

	// Disable all objects if exist
	for (int i = 0; i < _gameObjectManager->_objects.size(); ++i) {
		if (!_gameObjectManager->_objects[i]->IsUnique()) {
			_gameObjectManager->_objects[i]->Deactivate();
		}
	}
	_gameObjectManager->DeactivateObjects();

	// Load level settings
	std::string lv = "Levels/Level_";
	lv += ('0' + _level);

	_gameObjectManager->LoadLevel(JsonHandle::ReadFile(lv + ".json"));
	_gameObjectManager->Initialize();
	std::cout << "Total objects: " << _gameObjectManager->_objects.size() << std::endl;

	_state = STATE::LOOP;
	std::cout << "Initialize level " << _level << " successed" << std::endl;
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
	if (_inputManager->KeyTriggered(SDL_SCANCODE_R)) {
		_state = STATE::INIT;
		_settingsLoaded = false;
		return true;
	}
	if (_inputManager->KeyTriggered(SDL_SCANCODE_T)) {
		ProcceedLevel();
		return true;
	}
	if (_inputManager->KeyTriggered(SDL_SCANCODE_TAB)) {
		_renderManager->SwitchMode();
	}
	if (_inputManager->KeyTriggered(SDL_SCANCODE_Q)) {
		return false;
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

	// Clear objects that sould be inactive
	_gameObjectManager->DeactivateObjects();

	// Draw everything
	_renderManager->Draw();

	// update frame end time
	_framerateManager->FrameEnd();

	// Check SDL event
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0) {
		//User requests quit
		if (e.type == SDL_QUIT)
		{
			return false;
		}
		if (e.type == SDL_WINDOWEVENT) {
			if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
				std::cout << "Window resized to " << e.window.data1 << " x " << e.window.data2 << std::endl;
				_renderManager->ResizeWindow();
			}
		}
	}

	return true;
}

bool GameStateManager::RunGame()
{
	return (this->*(_gameStates[_state]))();
}

void GameStateManager::ProcceedLevel()
{
	_state = STATE::INIT;
	_level = (_level + 1) % 4;
}
