#pragma once
#include "Component.h"
#include "Transform.h"
#include "../GameObject.h"
#include <SDL_scancode.h>

class Controller : public Component
{
public:
	Controller();
	~Controller();

	void Update();
	void Serialize(std::string);

	void TriggerEvent();
};
