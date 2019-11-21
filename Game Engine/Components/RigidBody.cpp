#include "RigidBody.h"
#include "../Events/OnCollision.h"


RigidBody::RigidBody(): Component(COMPONENT_TYPE::RIGID_BODY), 
_velX(0.0f), _velY(0.0f), _accX(0.0f), _accY(0.0f), _posX(0.0f), _posY(0.0f), 
_mass(0.0f), _gravityScale(0.0f), _forceX(0.0f), _forceY(0.0f), _prevPosX(0.0f), _prevPosY(0.0f), _prevPosZ(0.0f)
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

	_accX = _forceX / _mass;
	_accY = _forceY / _mass;

	// consume force
	_forceX = 0.0f;
	_forceY = 0.0f;

	_velX += _accX * deltaTime;
	_velY += _accY * deltaTime;
	
	// Only affected by gravity
	_velZ -= gravity * _gravityScale * deltaTime;

	_posX += _velX * deltaTime;
	_posY += _velY * deltaTime;
	_posZ += _velZ * deltaTime;

	transform->_translateX = _posX;
	transform->_translateY = _posY;
	transform->_translateZ = _posZ;
}

void RigidBody::Stop()
{
	_accX = 0.0f;
	_accY = 0.0f;

	_velX = 0.0f;
	_velY = 0.0f;

	_forceX = 0.0f;
	_forceY = 0.0f;
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
		if (dynamic_cast<OnCollision*>(e)->_groundCollision) {
			// std::cout << _owner->GetTag() << " Hit!!" << std::endl;
			Transform * transform = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));
			transform->_translateZ = _prevPosZ;
			_velZ = 0;
		}
	}
	else if (e->GetType() == EVENT_TYPE::DELAY_MOVE) {
		Transform * transform = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));
		transform->_translateZ += 50;
	}
}