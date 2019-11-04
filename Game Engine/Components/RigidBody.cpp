#include "RigidBody.h"



RigidBody::RigidBody(): Component(COMPONENT_TYPE::RIGID_BODY), 
_velX(0.0f), _velY(0.0f), _accX(0.0f), _accY(0.0f), _posX(0.0f), _posY(0.0f), _mass(0.0f)
{
}


RigidBody::~RigidBody()
{
}

void RigidBody::Initialize()
{
}

void RigidBody::Integrate(float gravity, float deltaTime)
{
}

void RigidBody::Update()
{
	// Do nothing. Physic updates should be in another stage
	// done by physic manager
}

void RigidBody::Serialize(std::string data)
{
}