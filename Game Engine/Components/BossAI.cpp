#include "BossAI.h"
#include "Transform.h"
#include "RigidBody.h"
#include "../GameStateManager.h"
#include "../Events/GameOver.h"

#define MAX_ROTATE_SPEED 80
#define ATTACK_INTERVAL 120

extern GameStateManager * pMgr;

BossAI::BossAI(): Component(COMPONENT_TYPE::BOSS_AI), _state(0), _stateCounter(0), _spCounter(0)
{
}


BossAI::~BossAI()
{
}

void BossAI::Update()
{
	if (_state == 0) {
		if (_stateCounter < ATTACK_INTERVAL) {
			Transform * transform = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));
			float front_x = sin(transform->_rotateZ * PI / 180.0f);
			float front_y = -1 * cos(transform->_rotateZ * PI / 180.0f);

			Transform * t_transform = dynamic_cast<Transform*>(_target->GetComponent(COMPONENT_TYPE::TRANSFORM));
			float vec_x = t_transform->_translateX - transform->_translateX;
			float vec_y = t_transform->_translateY - transform->_translateY;

			float dotv = (vec_x * front_x + vec_y * front_y) / sqrt(vec_x * vec_x + vec_y * vec_y);
			if (dotv >= 1.0f) dotv = 1.0f;
			if (dotv <= -1.0f) dotv = -1.0f;
			float angle = acosf(dotv) * 180 / PI;

			if (angle > MAX_ROTATE_SPEED * pMgr->_framerateManager->_frameTime / 1000.0f) {
				angle = MAX_ROTATE_SPEED * pMgr->_framerateManager->_frameTime / 1000.0f;
			}

			if (front_x * vec_y - front_y * vec_x > 0)  transform->_rotateZ += angle;
			else transform->_rotateZ -= angle;

			++_stateCounter;
		}
		else {
			_state = 1;
			_stateCounter = 0;

			Collider * collider = dynamic_cast<Collider*>(_owner->GetComponent(COMPONENT_TYPE::COLLIDER));
			collider->_posZ = 0.1f;

			RigidBody * body = dynamic_cast<RigidBody*>(_owner->GetComponent(COMPONENT_TYPE::RIGID_BODY));
			body->_forceZ += 10000.0f;
		}
	}
	else if(_state == 1) {
		// Create and shoot a bullet
		GameObject * bullet = pMgr->_gameObjectManager->GetObject("projectile");
		dynamic_cast<Projectile*>(bullet->GetComponent(COMPONENT_TYPE::PROJECTILE))->SetShooter(_owner->GetTag());
		bullet->InitComponents();
		
		if (_spCounter < 5) {
			_state = 0;
			++_spCounter;
		}
		else {
			_state = 2;
			_spCounter = 0;
		}
	}
	else if (_state == 2) {
		Collider * collider = dynamic_cast<Collider*>(_owner->GetComponent(COMPONENT_TYPE::COLLIDER));
		collider->_posZ = 0.1f;

		RigidBody * body = dynamic_cast<RigidBody*>(_owner->GetComponent(COMPONENT_TYPE::RIGID_BODY));
		body->_forceZ += 35000.0f;

		_state = 3;
	}
	else if (_state == 3) {
		// Wait for fall on ground
	}
	else if (_state == 4) {
		if (_stateCounter < ATTACK_INTERVAL) {
			if (_stateCounter % 4 == 0) {
				for (int i = 0; i < 4; ++i) {
					GameObject * bullet = pMgr->_gameObjectManager->GetObject("projectile");
					bullet->InitComponents();
					Transform * b_transform = dynamic_cast<Transform*>(bullet->GetComponent(COMPONENT_TYPE::TRANSFORM));
					b_transform->_translateY = 40.0f;
					b_transform->_translateX = -15 + 10 * i;
				}
			}
			++_stateCounter;
		}
		else {
			_state = 0;
			_stateCounter = 0;
		}
	}

}

void BossAI::Serialize(json data)
{

}

void BossAI::Initialize()
{
	_target = pMgr->_gameObjectManager->_tagObjects.FindValueByKey("Player");
}

void BossAI::HandleEvent(Event * e)
{
	if (e->GetType() == EVENT_TYPE::ON_COLLISION) {
		OnCollision * on_c = dynamic_cast<OnCollision*>(e);
		if (on_c->_target == 0) {
			if (_state == 3) {
				_state = 4;
			}
		}
	}
	else if (e->GetType() == EVENT_TYPE::GAME_OVER) {
		GameOver * go = dynamic_cast<GameOver*>(e);
		if (go->_victory) {
			_state = 5;
		}
	}
}