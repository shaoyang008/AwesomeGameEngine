/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Transform.h
Purpose: Translate, Rotate, and Scale of an object
Language: C
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 10/19/2019

---------------------------------------------------------*/

#pragma once
#include <SDL_rect.h>
#include "Component.h"
#include "../GameObject.h"
#include "../Events/DelayMove.h"

class Transform : public Component
{
public:
	Transform();
	Transform(float, float);
	~Transform();

	void Update();
	void Serialize(json data);
	void HandleEvent(Event *);

	float _posX;
	float _posY;

	SDL_Rect * offset;
private:
};

