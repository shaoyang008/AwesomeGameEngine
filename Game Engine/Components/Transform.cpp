/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Transform.cpp
Purpose: Translate, Rotate, and Scale of an object
Language: C
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 10/19/2019

---------------------------------------------------------*/

#include "Transform.h"
#include "../GameStateManager.h"

extern GameStateManager *pMgr;

Transform::Transform(): Component(COMPONENT_TYPE::TRANSFORM), _translateX(0.0f), _translateY(0.0f), _translateZ(0.0f),
_scaleX(0.0f), _scaleY(0.0f), _scaleZ(0.0f), _rotateX(0.0f), _rotateY(0.0f), _rotateZ(0.0f)
{
   
}

Transform::~Transform()
{
}

void Transform::Update() 
{

}

void Transform::Serialize(json data)
{
	
	_translateX = data["TranslateX"].get<float>();
	_translateY = data["TranslateY"].get<float>();
	_translateZ = data["TranslateZ"].get<float>();

	_scaleX = data["ScaleX"].get<float>();
	_scaleY = data["ScaleY"].get<float>();
	_scaleZ = data["ScaleZ"].get<float>();

	_rotateX = data["RotateX"].get<float>();
	_rotateY = data["RotateY"].get<float>();
	_rotateZ = data["RotateZ"].get<float>();
}

void Transform::HandleEvent(Event *e) 
{

}