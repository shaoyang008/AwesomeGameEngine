#pragma once
#include "GameObject.h"
#include "Components/Base.h"
#include "Events/Event.h"
#include "Events/OnCollision.h"
#include <queue>

typedef struct LineSegment
{
	float x_start, y_start;
	float x_end, y_end;
} LineSegment;

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

	void CheckCollisions();
	bool StaticAABBtoStaticAABB(GameObject*, GameObject*);
	bool StaticAABBtoDynamicAABB(GameObject*, GameObject*);
	bool StaticAABBtoGround(GameObject *);

	// Dummy methods for work in progress
	// or methods that will be skipped in this project
	bool NotImplemented(GameObject*, GameObject*) { return false; }

	float LineSegtoLineSeg(LineSegment&, LineSegment&, int);

	void Enqueue(GameObject *, GameObject *);
	void ResolveCollisions();

private:
	std::queue<Collision*> _collisions;
	bool (CollisionManager::*_collisionTests[static_cast<int>(COLLIDER_TYPE::count)][static_cast<int>(COLLIDER_TYPE::count)])(GameObject*, GameObject*);
};

