/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Sprite.h
Purpose: Sprite of objects
Language: C
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 10/19/2019

---------------------------------------------------------*/

#pragma once
#include "Component.h"
#include "../GameObject.h"
#include "../Material.h"
#include "../ShaderProgram.h"

class Sprite : public Component
{
public:
	Sprite();
	~Sprite();

	void Update();
	void Serialize(json data);

	void UseSprite(ShaderProgram *);
	void Unuse();

	void SetTexture(Material *);

	float _posX, _posY;
	float _scaleX, _scaleY;

private:
	Material * _texture;
};

