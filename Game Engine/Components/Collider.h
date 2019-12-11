/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Collider.h
Purpose: Collider size and information
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

#pragma once
#include "Component.h"
#include "Transform.h"
#include "../ObjectModel.h"
#include "../ShaderProgram.h"
#include "../Utilities/Matrix4.h"
#include "../Utilities/Shape.h"


class Collider : public Component
{
public:
	enum TYPE {
		STATIC_AABB,
		DYNAMIC_AABB,
		STATIC_SPHERE,
		DYNAMIC_SPHERE,
		count
	};

	Collider();
	~Collider();

	void Update();
	void Serialize(json data);
	void Initialize();

	void Draw(ShaderProgram*);

	float _posX, _posY, _posZ;
	Shape * _shape;

	int GetType() { return _type; }

private:
	int _type;
};