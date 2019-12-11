/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Follow.cpp
Purpose: Follow its target from given distance
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

#include "Follow.h"
#include "Transform.h"
#include "../GameStateManager.h"

extern GameStateManager * pMgr;

Follow::Follow(): Component(COMPONENT_TYPE::FOLLOW), _distanceX(0.0f), _distanceY(0.0f)
{
}


Follow::~Follow()
{
}

void Follow::Update()
{
	Transform * transform = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));
	Transform * follow_transform = dynamic_cast<Transform*>(_followObject->GetComponent(COMPONENT_TYPE::TRANSFORM));

	transform->_translateX = follow_transform->_translateX + _distanceX;
	transform->_translateY = follow_transform->_translateY + _distanceY;
}

void Follow::Serialize(json data)
{
	_followTag = data["Tag"].get<std::string>();

	_distanceX = data["DistanceX"].get<float>();
	_distanceY = data["DistanceY"].get<float>();
}

void Follow::Initialize()
{
	_followObject = pMgr->_gameObjectManager->_tagObjects.FindValueByKey(_followTag);
}