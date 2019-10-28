#include "Controller.h"
#include "../GameStateManager.h"

extern GameStateManager *pMgr;

#define MOVEMENT_SPEED 5

Controller::Controller(): Component(COMPONENT_TYPE::CONTROLLER)
{
}


Controller::~Controller()
{
}

void Controller::Update()
{
}

void Controller::Serialize(std::string data)
{
}

void Controller::TriggerEvent()
{
	Transform * t = dynamic_cast<Transform*>(pOwner->GetComponent(COMPONENT_TYPE::TRANSFORM));
	if (!t) return;

	if (pMgr->pIM->key_pressed(SDL_SCANCODE_UP)) {
		t->_posY -= MOVEMENT_SPEED;
	}
	else if (pMgr->pIM->key_pressed(SDL_SCANCODE_DOWN)) {
		t->_posY += MOVEMENT_SPEED;
	}
	else if (pMgr->pIM->key_pressed(SDL_SCANCODE_LEFT)) {
		t->_posX -= MOVEMENT_SPEED;
	}
	else if (pMgr->pIM->key_pressed(SDL_SCANCODE_RIGHT)) {
		t->_posX += MOVEMENT_SPEED;
	}
}