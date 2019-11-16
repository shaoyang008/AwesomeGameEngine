#pragma once
#include "GameObject.h"
#include "Components/Base.h"
#include "Events/Event.h"
#include "Events/OnCollision.h"
#include <queue>

class Collision
{
public:
	Collision() {}
	Collision(GameObject *go1, GameObject *go2) : _go1(go1), _go2(go2) {}
	~Collision() {}

	GameObject* _go1;
	GameObject* _go2;
};

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void PlayerCollision(std::string);
	bool StaticAABBtoAABB(GameObject*, GameObject*);

	void Enqueue(GameObject *, GameObject *);
	void ResolveCollisions();

private:
	std::queue<Collision*> _collisions;
};

