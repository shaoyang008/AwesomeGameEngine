/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: EnemyAI.cpp
Purpose: Define enemy behaviors
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

#include "EnemyAI.h"
#include "../GameStateManager.h"
#include "../Events/PlayerHit.h"
#include "../Events/EnemyHit.h"

extern GameStateManager * pMgr;

#define MAX_ROTATE_SPEED 240
#define MOVEMENT_SPEED 24

EnemyAI::EnemyAI(): Component(COMPONENT_TYPE::ENEMY_AI), _state(0), _target(0),
_size(0), _speeds(0), _endpoints(0), _atkState(0), _atkFrames(false)
{
}


EnemyAI::~EnemyAI()
{
	delete[] _speeds;
	delete[] _endpoints;
}

void EnemyAI::Update()
{
	// Three states
	// 0. track player
	// 1. rotate to player
	// 2. Follow Up
	// 3. If near enough, attack
	// Else repeat and track again
	if (_state == 0) {
		Transform * transform = dynamic_cast<Transform*>(_target->GetComponent(COMPONENT_TYPE::TRANSFORM));
		_targetX = transform->_translateX;
		_targetY = transform->_translateY;
		_state = 1;
	}
	else if (_state == 1) {
		Transform * transform = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));

		float front_x = sin(transform->_rotateZ * PI / 180.0f);
		float front_y = -1 * cos(transform->_rotateZ * PI / 180.0f);

		float vec_x = _targetX - transform->_translateX;
		float vec_y = _targetY - transform->_translateY;

		float dotv = (vec_x * front_x + vec_y * front_y) / sqrt(vec_x * vec_x + vec_y * vec_y);
		if (dotv >= 1.0f) dotv = 1.0f;
		if (dotv <= -1.0f) dotv = -1.0f;
		float angle = acosf(dotv) * 180 / PI;
		if (angle < 0.1f) {
			_state = 2;
		}
		else {
			if (angle > MAX_ROTATE_SPEED * pMgr->_framerateManager->_frameTime / 1000.0f) {
				angle = MAX_ROTATE_SPEED * pMgr->_framerateManager->_frameTime / 1000.0f;
			}

			if (front_x * vec_y - front_y * vec_x > 0)  transform->_rotateZ += angle;
			else transform->_rotateZ -= angle;
		}
	}
	else if (_state == 2) {
		Transform * transform = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));
		RigidBody * body = dynamic_cast<RigidBody*>(_owner->GetComponent(COMPONENT_TYPE::RIGID_BODY));

		float dist = (transform->_translateX - _targetX) * (transform->_translateX - _targetX) + (transform->_translateY - _targetY) * (transform->_translateY - _targetY);
		if (dist < 10) {
			body->_vel = 0;
			_state = 0;
		}
		else {
			body->_vel = MOVEMENT_SPEED;
		}
	}
	else if (_state == 3) {
		Transform* transform = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));
		RigidBody * body = dynamic_cast<RigidBody*>(_owner->GetComponent(COMPONENT_TYPE::RIGID_BODY));
		body->_vel = 0;

		if(_atkState < _size) {
			transform->_rotateX += _speeds[_atkState] * pMgr->_framerateManager->_frameTime / 1000.0f;
			if (transform->_rotateX * _speeds[_atkState] > _endpoints[_atkState] * _speeds[_atkState]) ++_atkState;
			if (_atkState == _size - 1) ++_atkFrames;
		}
		else {
			transform->_rotateX = 0;
			_state = 0;

			// Reset attack
			_atkFrames = 0;
		}
	}
	else if (_state >= 4) {
		Transform* transform = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));
		transform->_scaleX *= 0.8f;
		transform->_scaleY *= 0.8f;
		transform->_scaleZ *= 0.8f;

		RigidBody * body = dynamic_cast<RigidBody*>(_owner->GetComponent(COMPONENT_TYPE::RIGID_BODY));
		body->_vel = 10;
		
		++_state;
		if (_state > 100) {
			Reborn();
		}
	}
}

void EnemyAI::Serialize(json data)
{
	_size = data["Size"].get<int>();

	_speeds = new float[_size];
	for (int i = 0; i < _size; ++i) {
		_speeds[i] = data["Speed"][i].get<float>();
	}

	_endpoints = new float[_size];
	for (int i = 0; i < _size; ++i) {
		_endpoints[i] = data["Endpoint"][i].get<float>();
	}
}

void EnemyAI::Initialize()
{
	_target = pMgr->_gameObjectManager->_tagObjects.FindValueByKey("Player");
	_state = 0;
	_atkState = 0;

	Transform * transform = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));
	transform->_rotateX = 0;
	transform->_scaleX = 0.5;
	transform->_scaleY = 0.5;
	transform->_scaleZ = 0.5;
}

void EnemyAI::HandleEvent(Event * e)
{
	if (e->GetType() == EVENT_TYPE::ON_COLLISION) {
		OnCollision * on_c = dynamic_cast<OnCollision*>(e);
		if (on_c->_target && on_c->_target->GetType() == "player") {
			Transform * transform = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));
			float front_x = sin(transform->_rotateZ * PI / 180.0f);
			float front_y = -1 * cos(transform->_rotateZ * PI / 180.0f);

			Transform * t_transform = dynamic_cast<Transform*>(_target->GetComponent(COMPONENT_TYPE::TRANSFORM));
			float vec_x = t_transform->_translateX - transform->_translateX;
			float vec_y = t_transform->_translateY - transform->_translateY;

			float dotv = (vec_x * front_x + vec_y * front_y) / sqrt(vec_x * vec_x + vec_y * vec_y);

			if (dotv > 0.6) {
				if (_state < 3) {
					_atkState = 0;
					_state = 3;
				}
				else if(_state == 3) {
					if (_atkFrames <= 5 && _atkState == _size - 1) {
						// std::cout << "Player got hit!!" << std::endl;
						Event * e_new = new PlayerHit;
						pMgr->_eventManager->Enque(e_new);

						_atkFrames = 5;
					}
				}
			}
		}
	}
	else if (e->GetType() == EVENT_TYPE::ENEMY_HIT) {
		EnemyHit * eh = dynamic_cast<EnemyHit*>(e);
		if (eh->_specialAtk) {
			if(_state < 4) _state = 4;
			// std::cout << _owner->GetTag() << " being sucked " << _state << std::endl;
		}
		else {
			Reborn();
		}
	}
}

void EnemyAI::Reborn()
{
	Transform * transform = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));

	int random_position = rand() % 220 - 110;
	int random_direction = rand() % 4;

	if (random_direction < 2) {
		if (random_direction == 0) {
			transform->_translateX = -110;
		}
		else {
			transform->_translateX = 110;
		}
		transform->_translateY = random_position;
	}
	else {
		if (random_direction == 2) {
			transform->_translateY = -110;
		}
		else {
			transform->_translateY = 110;
		}
		transform->_translateX = random_position;
	}
	_owner->InitComponents();
	std::cout << _owner->GetTag() << " reborn at " << transform->_translateX << ", " << transform->_translateY << std::endl;
}
