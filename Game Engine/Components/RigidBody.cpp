#include "RigidBody.h"
#include "../Events/OnCollision.h"

RigidBody::RigidBody(): Component(COMPONENT_TYPE::RIGID_BODY), 
_vel(0.0f), _velZ(0.0f), _acc(0.0f), _accZ(0.0f), _posX(0.0f), _posY(0.0f), _posZ(0.0f),
_force(0.0f), _forceZ(0.0f), _mass(0.0f), _gravityScale(0.0f), _prevPosX(0.0f), _prevPosY(0.0f), _prevPosZ(0.0f)
{
}


RigidBody::~RigidBody()
{
}

void RigidBody::Initialize()
{
	Transform * transform = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));
	_posX = transform->_translateX;
	_posY = transform->_translateY;
	_posZ = transform->_translateZ;
}

void RigidBody::Integrate(float gravity, float deltaTime)
{
	Transform * transform = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));
	_posX = transform->_translateX;
	_posY = transform->_translateY;
	_posZ = transform->_translateZ;

	// Remember position before updated
	_prevPosX = _posX;
	_prevPosY = _posY;
	_prevPosZ = _posZ;

	_acc = _force / _mass;
	_accZ = _forceZ / _mass + gravity * _gravityScale;

	_vel += _acc * deltaTime;
	_velZ += _accZ * deltaTime;

	_posX += _vel * deltaTime * sin(transform->_rotateZ * PI / 180.0f);
	_posY -= _vel * deltaTime * cos(transform->_rotateZ * PI / 180.0f);
	_posZ += _velZ * deltaTime;

	transform->_translateX = _posX;
	transform->_translateY = _posY;
	transform->_translateZ = _posZ;

	// consume force
	_force = 0.0f;
	_forceZ = 0.0f;
}

void RigidBody::Stop()
{
	_acc = 0.0f;
	_vel = 0.0f;
	_force = 0.0f;
}

void RigidBody::Update()
{
	// Do nothing. Physic updates should be in another stage
	// done by physic manager
}

void RigidBody::Serialize(json data)
{
	_mass = data["Mass"].get<float>();
	_gravityScale = data["Scale"].get<float>();
}

void RigidBody::HandleEvent(Event * e)
{
	if (e->GetType() == EVENT_TYPE::ON_COLLISION) {
		OnCollision * on_c = dynamic_cast<OnCollision*>(e);
		if (on_c->_target == 0) {
			Transform * transform = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));
			transform->_translateZ = 0;
			_velZ = 0.0f;
			_accZ = 0.0f;
			_forceZ = 0.0f;
		}
		else {
			if (_owner->GetType() == "player") {
				if (on_c->_target->GetType() == "static_object" ||
					on_c->_target->GetType() == "ground"
					) {
					Transform* transform = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));
					transform->_translateX = _prevPosX;
					transform->_translateY = _prevPosY;
					Stop();
				}
			}
		}
	}
	else if (e->GetType() == EVENT_TYPE::DELAY_MOVE) {
		Transform * transform = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));
		transform->_translateZ += 15;
	}
}