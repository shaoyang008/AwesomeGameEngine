#pragma once
#include "Component.h"
#include "Transform.h"

class RigidBody : public Component
{
public:
	RigidBody();
	~RigidBody();

	void Update();
	void Serialize(json data);

	// Initialize physic values
	void Initialize();
	// Add up all forces in dt and apply to objects
	void Integrate(float, float);
	void Stop();

	float _forceX, _forceY;

private:
	float _velX, _velY;
	float _accX, _accY;
	float _posX, _posY;
	float _mass, _gravityScale;
};

