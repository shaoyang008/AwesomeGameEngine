#pragma once
#include <SDL_rect.h>
#include "Component.h"
#include "../GameObject.h"

class Transform : public Component
{
public:
	Transform();
	Transform(float, float);
	~Transform();

	void Update();
	void Serialize(std::string);

	float _posX;
	float _posY;

	SDL_Rect * offset;
private:
};

