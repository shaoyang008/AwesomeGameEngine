/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: NormalAtk.cpp
Purpose: Normal attack for player
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

#include "NormalAtk.h"
#include "Model.h"
#include "../GameObject.h"
#include "../GameStateManager.h"
#include "../Events/ToggleAttack.h"
#include "../Events/EnemyHit.h"

#define MAX_ATK_FRAME 15

extern GameStateManager *pMgr;

NormalAtk::NormalAtk(): Component(COMPONENT_TYPE::NORMAL_ATK), _original(0), _animation(0), _atkFrames(0)
{
}


NormalAtk::~NormalAtk()
{
}

void NormalAtk::Initialize()
{
	Model * model = dynamic_cast<Model*>(_owner->GetComponent(COMPONENT_TYPE::MODEL));
	_original = model->_modelRoot;
}

void NormalAtk::Update()
{
	if(_atkFrames < MAX_ATK_FRAME) {
		++_atkFrames;
	}
	else if (_atkFrames == MAX_ATK_FRAME) {
		Model * model = dynamic_cast<Model*>(_owner->GetComponent(COMPONENT_TYPE::MODEL));
		model->_modelRoot = _original;
		++_atkFrames;
	}
}

void NormalAtk::Serialize(json data)
{
	std::string path = "Resources/Models/" + data["Filename"].get<std::string>();
	Load(path);
}

bool NormalAtk::Load(std::string path)
{
	if (!pMgr->_resourceManager->RegisterModel(path)) {
		std::cout << "Could not load resource: " << path << std::endl;
		return false;
	}
	_animation = pMgr->_resourceManager->GetModelByPath(path);
	return true;
}

void NormalAtk::HandleEvent(Event * e)
{
	if (e->GetType() == EVENT_TYPE::TOGGLE_ATTACK) {
		ToggleAttack * t = dynamic_cast<ToggleAttack*>(e);
		if (t->_atkType == 0) {
			if (_atkFrames > MAX_ATK_FRAME) {
				Model * model = dynamic_cast<Model*>(_owner->GetComponent(COMPONENT_TYPE::MODEL));
				model->_modelRoot = _animation;

				_atkFrames = 0;
			}
		}
	}
	else if (e->GetType() == EVENT_TYPE::ON_COLLISION) {
		OnCollision * oc = dynamic_cast<OnCollision*>(e);
		if (oc->_target && (oc->_target->GetType() == "enemy" || oc->_target->GetType() == "boss")) {
			if (_atkFrames < MAX_ATK_FRAME) {
				// TODO: Enemy Hit event
				// Reset it somewhere outside the map
				Transform * o_transform = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));
				float front_x = sin(o_transform->_rotateZ * PI / 180.0f);
				float front_y = -1 * cos(o_transform->_rotateZ * PI / 180.0f);

				Transform * transform = dynamic_cast<Transform*>(oc->_target->GetComponent(COMPONENT_TYPE::TRANSFORM));
				float vec_x = transform->_translateX - o_transform->_translateX;
				float vec_y = transform->_translateY - o_transform->_translateY;

				float dotv = (vec_x * front_x + vec_y * front_y) / sqrt(vec_x * vec_x + vec_y * vec_y);

				if (dotv > 0.6) {
					Event * new_e = new EnemyHit;
					oc->_target->ReceiveEvent(new_e);
				}

				if (oc->_target->GetType() == "boss") {
					_atkFrames = MAX_ATK_FRAME;
				}
			}
		}
	}
}
