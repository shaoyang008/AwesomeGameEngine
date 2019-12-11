/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Light.h
Purpose: Lighting information for drawing
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

#pragma once
#include "Component.h"

class Light : public Component
{
public:
	Light();
	~Light();

	void Update();
	void Serialize(json);

	float _ambient[3];
	float _light[3];
	float _lightPos[3];
	float _angle;
};

