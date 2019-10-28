#include "GameStateManager.h"

#define MOVEMENT_SPEED 5

GameStateManager::GameStateManager(): pIM(new InputManager), pFM(new FramerateManager(60)), pRM(new ResourceManager),
pGOM(new GameObjectManager)
{

}

GameStateManager::~GameStateManager()
{
	pRM->FreeAll();
	delete pIM;
	delete pFM;
	delete pRM;
	delete pGOM;
}

void GameStateManager::SetWindow(SDL_Window * window) {
	pWindow = window;
	pWindowSurface = SDL_GetWindowSurface(pWindow);
}

bool GameStateManager::Load()
{
	return false;
}

bool GameStateManager::Init()
{
	Sprite * ps;

	// Build Background
	GameObject *pBackground = pGOM->CreateObject(OBJECT_TYPE::IMAGE, "background");
	std::string path = "Resources/background.bmp";
	if (!pRM->RegisterSurface(path)) {
		printf("Could not load resource: %s\nReason: %s", path, SDL_GetError());
		return false;
	}
	ps = dynamic_cast<Sprite*>(pBackground->GetComponent(COMPONENT_TYPE::SPRITE));
	if (ps) {
		ps->pSurface = pRM->GetSurfaceByPath(path);
	}

	pGOM->LoadObject("player");
	pGOM->LoadObject("enemy1");
	pGOM->LoadObject("enemy2");

	return true;
}

bool GameStateManager::Loop()
{

	// Record frame start time
	pFM->FrameStart();

	// Draw Background
	for (int i = 0; i < pGOM->_objects.size(); ++i) {
		Sprite    * s = dynamic_cast<Sprite*>(pGOM->_objects[i]->GetComponent(COMPONENT_TYPE::SPRITE));
		Transform * t = dynamic_cast<Transform*>(pGOM->_objects[i]->GetComponent(COMPONENT_TYPE::TRANSFORM));
		if (s && t) { SDL_BlitSurface(s->pSurface, NULL, pWindowSurface, t->offset); }
	}

	SDL_UpdateWindowSurface(pWindow);
	
	pIM->update_state();
	if (pIM->key_pressed(SDL_SCANCODE_Q)) {
		return false;
	}

	
	for (int i = 0; i < pGOM->_objects.size(); ++i) {
		Controller * ctrl = dynamic_cast<Controller*>(pGOM->_objects[i]->GetComponent(COMPONENT_TYPE::CONTROLLER));
		if(ctrl) ctrl->TriggerEvent();
	}

	// Update all game objects
	pGOM->Update();

	// update frame end time
	pFM->FrameEnd();
	return true;
}