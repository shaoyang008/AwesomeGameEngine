/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: SpecialAtk.cpp
Purpose: Special attack for player
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

#include "SpecialAtk.h"
#include "Model.h"
#include "../GameObject.h"
#include "../GameStateManager.h"
#include "../Events/ToggleAttack.h"
#include "../Events/EnemyHit.h"

extern GameStateManager *pMgr;

SpecialAtk::SpecialAtk() : Component(COMPONENT_TYPE::SPECIAL_ATK), _animation(0), _original(0), _toggleAtk(false)
{
}


SpecialAtk::~SpecialAtk()
{
}

void SpecialAtk::Update()
{
}

void SpecialAtk::Serialize(json data)
{
	std::string path = "Resources/Models/" + data["Filename"].get<std::string>();
	Load(path);
}

bool SpecialAtk::Load(std::string path)
{
	if (!pMgr->_resourceManager->RegisterModel(path)) {
		std::cout << "Could not load resource: " << path << std::endl;
		return false;
	}
	_animation = pMgr->_resourceManager->GetModelByPath(path);
	return true;
}

void SpecialAtk::Initialize()
{
	Model * model = dynamic_cast<Model*>(_owner->GetComponent(COMPONENT_TYPE::MODEL));
	_original = model->_modelRoot;
	_toggleAtk = false;
}

void SpecialAtk::HandleEvent(Event * e)
{
	if (e->GetType() == EVENT_TYPE::TOGGLE_ATTACK) {
		ToggleAttack * t = dynamic_cast<ToggleAttack*>(e);
		if (t->_atkType == 1) {
			Model * model = dynamic_cast<Model*>(_owner->GetComponent(COMPONENT_TYPE::MODEL));
			model->_modelRoot = _animation;
			_toggleAtk = true;
		}
		if (t->_atkType == 2) {
			Model * model = dynamic_cast<Model*>(_owner->GetComponent(COMPONENT_TYPE::MODEL));
			model->_modelRoot = _original;
			_toggleAtk = false;
		}
	}
	else if (e->GetType() == EVENT_TYPE::ON_COLLISION) {
		OnCollision * oc = dynamic_cast<OnCollision*>(e);
		if (oc->_target && (oc->_target->GetType() == "enemy")) {
			if (_toggleAtk) {
				// TODO: Enemy Hit event
				// Reset it somewhere outside the map
				Transform * o_transform = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));
				float front_x = sin(o_transform->_rotateZ * PI / 180.0f);
				float front_y = -1 * cos(o_transform->_rotateZ * PI / 180.0f);

				Transform * transform = dynamic_cast<Transform*>(oc->_target->GetComponent(COMPONENT_TYPE::TRANSFORM));
				float vec_x = transform->_translateX - o_transform->_translateX;
				float vec_y = transform->_translateY - o_transform->_translateY;

				float dotv = (vec_x * front_x + vec_y * front_y) / sqrt(vec_x * vec_x + vec_y * vec_y);

				if (dotv > 0.0f) {
					Event * new_e = new EnemyHit(true);
					oc->_target->ReceiveEvent(new_e);
				}
			}
		}
	}
	else if (e->GetType() == EVENT_TYPE::GAME_OVER) {
		_toggleAtk = false;
	}
}

