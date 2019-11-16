#include "RigidBody.h"



RigidBody::RigidBody(): Component(COMPONENT_TYPE::RIGID_BODY), 
_velX(0.0f), _velY(0.0f), _accX(0.0f), _accY(0.0f), _posX(0.0f), _posY(0.0f), 
_mass(0.0f), _gravityScale(0.0f), _forceX(0.0f), _forceY(0.0f)
{
}


RigidBody::~RigidBody()
{
}

void RigidBody::Initialize()
{
	Transform * transform = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));
	_posX = transform->_posX;
	_posY = transform->_posY;
}

void RigidBody::Integrate(float gravity, float deltaTime)
{
	Transform * transform = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));
	_posX = transform->_posX;
	_posY = transform->_posY;

	_accX = _forceX / _mass;
	_accY = _forceY / _mass + gravity * _gravityScale;

	// consume force
	_forceX = 0.0f;
	_forceY = 0.0f;

	_velX += _accX * deltaTime;
	_velY += _accY * deltaTime;

	_posX += _velX * deltaTime;
	_posY += _velY * deltaTime;

	transform->_posX = _posX;
	transform->_posY = _posY;
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
	_mass = std::stof(data["Mass"].get<std::string>());
	_gravityScale = std::stof(data["Scale"].get<std::string>());
}