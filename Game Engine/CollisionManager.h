#pragma once
#include "GameObject.h"
#include "Components/Base.h"

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void PlayerCollision(std::string);
	bool StaticAABBtoAABB(GameObject*, GameObject*);
};

