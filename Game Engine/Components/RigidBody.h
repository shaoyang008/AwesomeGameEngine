#pragma once
#include "Component.h"

class RigidBody : public Component
{
public:
	RigidBody();
	~RigidBody();

	void Update();
	void Serialize(std::string data);

	// Initialize physic values
	void Initialize();
	// Add up all forces in dt and apply to objects
	void Integrate(float, float);

private:
	float _velX, _velY;
	float _accX, _accY;
	float _posX, _posY;
	float _mass;
};

