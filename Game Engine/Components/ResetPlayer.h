#pragma once
#include "Component.h"
#include "Transform.h"
#include "RigidBody.h"
#include "../GameObject.h"
#include "../Events/OnCollision.h"

class ResetPlayer : public Component
{
public:
	ResetPlayer();
	~ResetPlayer();

	void Update();
	void Serialize(json);
	void Initialize();
	void HandleEvent(Event *);

private:
	float _posX, _posY;
};

