/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: CollisionManager.h
Purpose: Calculate all collisions
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

#pragma once
#include "GameObject.h"
#include "Components/Base.h"
#include "Events/Event.h"
#include "Events/OnCollision.h"
#include "Utilities/Vector2D.h"
#include <queue>
#include <utility> 

typedef struct LineSegment
{
	float x_start, y_start;
	float x_end, y_end;
} LineSegment;

typedef std::pair<GameObject*, GameObject*> Collision;

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void CheckCollisions();
	bool StaticAABBtoStaticAABB(GameObject*, GameObject*);
	bool StaticAABBtoDynamicAABB(GameObject*, GameObject*);
	bool ObjecttoGround(GameObject *);
	bool StaticSpheretoStaticPoint(GameObject*, GameObject*);
	bool StaticSpheretoDynamicPoint(GameObject*, GameObject*);
	bool DynamicSpheretoDynamicPoint(GameObject*, GameObject*);

	// Dummy methods for work in progress
	// or methods that will be skipped in this project
	bool CollisionNotImplemented(GameObject*, GameObject*) { return false; }

	float LineSegtoLineSeg(LineSegment&, LineSegment&, int);

	void Enqueue(GameObject *, GameObject *);
	void ResolveCollisions();

private:
	std::queue<Collision> _collisions;
	bool (CollisionManager::*_collisionTests[Collider::TYPE::count][Collider::TYPE::count])(GameObject*, GameObject*);
};

