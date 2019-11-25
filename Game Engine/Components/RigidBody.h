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

	float _force, _forceZ;
	float _vel, _velZ;
	float _acc, _accZ;

	float _posX, _posY, _posZ;
	float _prevPosX, _prevPosY, _prevPosZ;

private:
	float _mass, _gravityScale;
};

