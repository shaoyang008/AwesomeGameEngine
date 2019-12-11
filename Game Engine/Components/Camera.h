/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Camera.h
Purpose: Camera viewing information
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

#pragma once
#include "Component.h"
#include <string>

#include "glm/glm.hpp"
using namespace glm;

class Camera : public Component
{
public:
	Camera();
	~Camera();

	void Update();
	void Serialize(json);
	void Initialize();

	float _ry;
	float _front, _back;
	float _tile, _spin;

	vec3 _position;

	std::string _targetTag;
	GameObject * _target;
	vec3 _targetPosition;

};

