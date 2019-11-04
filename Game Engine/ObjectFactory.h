/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: ObjectFactory.h
Purpose: Creates objects depend on input data
Language: C
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 10/26/2019

---------------------------------------------------------*/

#pragma once
#include "Components/Base.h"
#include "GameObject.h"
#include "json.hpp"

using json = nlohmann::json;

class ObjectFactory
{
public:
	ObjectFactory();
	~ObjectFactory();

	GameObject * CreateObject(json);
};

