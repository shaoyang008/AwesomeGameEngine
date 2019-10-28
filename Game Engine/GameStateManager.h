#pragma once

#include <SDL.h>
#include <fstream>
#include "FramerateManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "GameObjectManager.h"

class GameStateManager {
public:
	GameStateManager();
	~GameStateManager();

	void SetWindow(SDL_Window *);

	bool Load();
	bool Init();
	bool Loop();

	// Add managers here to do different tasks
	FramerateManager *pFM;
	InputManager *pIM;
	ResourceManager *pRM;
	GameObjectManager * pGOM;

private:
	SDL_Window *pWindow;
	SDL_Surface * pWindowSurface;
};