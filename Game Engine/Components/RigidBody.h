#pragma once
#include "Component.h"
#include "Transform.h"

class RigidBody : public Component
{
public:
	RigidBody();
	~RigidBody();

	void Update();
	void Serialize(json);

	// Initialize physic values
	void Initialize();
	void HandleEvent(Event *);

	// Add up all forces in dt and apply to objects
	void Integrate(float, float);
	void Stop();

	float _forceX, _forceY;

private:
	float _velX, _velY, _velZ;
	float _accX, _accY;
	float _posX, _posY, _posZ;
	float _prevPosX, _prevPosY, _prevPosZ;
	float _mass, _gravityScale;
};

