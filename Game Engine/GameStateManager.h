/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: GameStateManager.h
Purpose: Details of different stages of game loops
Language: C
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 10/18/2019

---------------------------------------------------------*/

#pragma once

#include <SDL.h>
#include <fstream>
#include "FramerateManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "RenderManager.h"
#include "GameObjectManager.h"
#include "PhysicsManager.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include "Events/DelayMove.h"

enum STATE {
	LOAD,
	INIT,
	LOOP,
	count
};

class GameStateManager {
public:
	GameStateManager();
	~GameStateManager();

	void SetWindow(SDL_Window *);
	void LoadSettings();

	bool Load();
	bool Init();
	bool Loop();
	bool RunGame();

	void ProcceedLevel();

	// Add managers here to do different tasks
	FramerateManager	*_framerateManager;
	InputManager		*_inputManager;
	ResourceManager		*_resourceManager;
	GameObjectManager	*_gameObjectManager;
	PhysicsManager		*_physicsManager;
	CollisionManager	*_collisionManager;
	EventManager		*_eventManager;
	RenderManager		*_renderManager;

private:
	SDL_Window *_window;
	SDL_Surface * _windowSurface;
	int _level;
	int _state;
	bool (GameStateManager::*_gameStates[STATE::count])(void);
	bool _settingsLoaded;
};