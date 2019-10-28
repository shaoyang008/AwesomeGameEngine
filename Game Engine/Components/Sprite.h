#pragma once
#include <SDL_surface.h>
#include "Component.h"
#include "../GameObject.h"

// extern resource_manager;

class Sprite : public Component
{
public:
	Sprite();
	~Sprite();

	void Update();
	void Serialize(std::string);

	SDL_Surface *pSurface;
private:
};

