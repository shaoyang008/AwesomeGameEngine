#include "CollisionManager.h"
#include "GameStateManager.h"

extern GameStateManager *pMgr;


CollisionManager::CollisionManager()
{
	for (int i = 0; i < Collider::TYPE::count; ++i) {
		for (int j = 0; j < Collider::TYPE::count; ++j) {
			_collisionTests[i][j] = &CollisionManager::CollisionNotImplemented;
		}
	}
	// All collision methods between different types of objects
	// Types are defined in COLLIDER_TYPE
	// 0: static aabb			1: dynamic aabb
	// 2: static sphere	(WIP)	3: dynamic sphere (WIP)
	_collisionTests[Collider::TYPE::STATIC_AABB][Collider::TYPE::STATIC_AABB] = &CollisionManager::StaticAABBtoStaticAABB;
	_collisionTests[Collider::TYPE::DYNAMIC_AABB][Collider::TYPE::STATIC_AABB] = &CollisionManager::StaticAABBtoDynamicAABB;
	_collisionTests[Collider::TYPE::DYNAMIC_SPHERE][Collider::TYPE::STATIC_AABB] = &CollisionManager::StaticSpheretoStaticPoint;
	_collisionTests[Collider::TYPE::STATIC_SPHERE][Collider::TYPE::DYNAMIC_AABB] = &CollisionManager::StaticSpheretoDynamicPoint;
	_collisionTests[Collider::TYPE::DYNAMIC_SPHERE][Collider::TYPE::DYNAMIC_AABB] = &CollisionManager::DynamicSpheretoDynamicPoint;
}


CollisionManager::~CollisionManager()
{
}

void CollisionManager::CheckCollisions()
{
	// Update all colliders position after physic update
	for (int i = 0; i < pMgr->_gameObjectManager->_objects.size(); ++i) {
		Collider * collider = dynamic_cast<Collider*>(pMgr->_gameObjectManager->_objects[i]->GetComponent(COMPONENT_TYPE::COLLIDER));
		if (collider) collider->Update();
	}
	
	for (int i = 0; i < pMgr->_gameObjectManager->_objects.size(); ++i) {
		GameObject * obj1 = pMgr->_gameObjectManager->_objects[i];
		if (ObjecttoGround(obj1)) {
			// std::cout << obj1->GetTag() << " hits the ground." << std::endl;
			Enqueue(obj1, 0);
		}

		for (int j = i + 1; j < pMgr->_gameObjectManager->_objects.size(); ++j) {
			GameObject * obj2 = pMgr->_gameObjectManager->_objects[j];

			Collider * c1 = dynamic_cast<Collider*>(obj1->GetComponent(COMPONENT_TYPE::COLLIDER));
			Collider * c2 = dynamic_cast<Collider*>(obj2->GetComponent(COMPONENT_TYPE::COLLIDER));
			if (!c1 || !c2) {
				continue;
			}
			else if ((this->*_collisionTests[c1->GetType()][c2->GetType()])(obj1, obj2)) {
				// std::cout << obj1->GetTag() << " collides with " << obj2->GetTag() << std::endl;
				Enqueue(obj1, obj2);
			}
			else if ((this->*_collisionTests[c2->GetType()][c1->GetType()])(obj2, obj1)) {
				// std::cout << obj2->GetTag() << " collides with " << obj1->GetTag() << std::endl;
				Enqueue(obj1, obj2);
			}
		}
	}
}

bool CollisionManager::StaticAABBtoStaticAABB(GameObject * g1, GameObject * g2)
{
	Collider * c1 = dynamic_cast<Collider*>(g1->GetComponent(COMPONENT_TYPE::COLLIDER));
	Collider * c2 = dynamic_cast<Collider*>(g2->GetComponent(COMPONENT_TYPE::COLLIDER));

	return (!(
		(c1->_posX - c1->_shape->GetRange(0) / 2 > c2->_posX + c2->_shape->GetRange(0) / 2) ||
		(c1->_posX + c1->_shape->GetRange(0) / 2 < c2->_posX - c2->_shape->GetRange(0) / 2) ||
		(c1->_posY - c1->_shape->GetRange(1) / 2 > c2->_posY + c2->_shape->GetRange(1) / 2) ||
		(c1->_posY + c1->_shape->GetRange(1) / 2 < c2->_posY - c2->_shape->GetRange(1) / 2)
	));
}

bool CollisionManager::StaticAABBtoDynamicAABB(GameObject * go_dynamic, GameObject * go_static)
{
	Collider * c1 = dynamic_cast<Collider*>(go_dynamic->GetComponent(COMPONENT_TYPE::COLLIDER));
	Collider * c2 = dynamic_cast<Collider*>(go_static->GetComponent(COMPONENT_TYPE::COLLIDER));

	// dynamic object must have rigid body component to perform motions
	RigidBody * body = dynamic_cast<RigidBody*>(go_dynamic->GetComponent(COMPONENT_TYPE::RIGID_BODY));
	if (!body) return false;

	std::vector<float> intersect_time;

	// Calculate four points of previous frame
	LineSegment line_segments[4];
	line_segments[0].x_start = body->_prevPosX - c1->_shape->GetRange(0) / 2; line_segments[0].y_start = body->_prevPosY - c1->_shape->GetRange(1) / 2;
	line_segments[1].x_start = body->_prevPosX + c1->_shape->GetRange(0) / 2; line_segments[1].y_start = body->_prevPosY - c1->_shape->GetRange(1) / 2;
	line_segments[2].x_start = body->_prevPosX - c1->_shape->GetRange(0) / 2; line_segments[2].y_start = body->_prevPosY + c1->_shape->GetRange(1) / 2;
	line_segments[3].x_start = body->_prevPosX + c1->_shape->GetRange(0) / 2; line_segments[3].y_start = body->_prevPosY + c1->_shape->GetRange(1) / 2;

	// Calculate four points of current frame
	line_segments[0].x_end = body->_posX - c1->_shape->GetRange(0) / 2; line_segments[0].y_end = body->_posY - c1->_shape->GetRange(1) / 2;
	line_segments[1].x_end = body->_posX + c1->_shape->GetRange(0) / 2; line_segments[1].y_end = body->_posY - c1->_shape->GetRange(1) / 2;
	line_segments[2].x_end = body->_posX - c1->_shape->GetRange(0) / 2; line_segments[2].y_end = body->_posY + c1->_shape->GetRange(1) / 2;
	line_segments[3].x_end = body->_posX + c1->_shape->GetRange(0) / 2; line_segments[3].y_end = body->_posY + c1->_shape->GetRange(1) / 2;

	// Calculate four bounds of static object
	LineSegment bounds[4];
	// left bound
	bounds[0].x_start = c2->_posX - c2->_shape->GetRange(0) / 2; bounds[0].y_start = c2->_posY - c2->_shape->GetRange(1) / 2;
	bounds[0].x_end = c2->_posX - c2->_shape->GetRange(0) / 2;   bounds[0].y_end = c2->_posY + c2->_shape->GetRange(1) / 2;
	// right bound
	bounds[1].x_start = c2->_posX + c2->_shape->GetRange(0) / 2; bounds[1].y_start = c2->_posY - c2->_shape->GetRange(1) / 2;
	bounds[1].x_end = c2->_posX + c2->_shape->GetRange(0) / 2;   bounds[1].y_end = c2->_posY + c2->_shape->GetRange(1) / 2;
	// lower bound
	bounds[2].x_start = c2->_posX - c2->_shape->GetRange(0) / 2; bounds[2].y_start = c2->_posY - c2->_shape->GetRange(1) / 2;
	bounds[2].x_end = c2->_posX + c2->_shape->GetRange(0) / 2;   bounds[2].y_end = c2->_posY - c2->_shape->GetRange(1) / 2;
	// upper bound
	bounds[3].x_start = c2->_posX - c2->_shape->GetRange(0) / 2; bounds[3].y_start = c2->_posY + c2->_shape->GetRange(1) / 2;
	bounds[3].x_end = c2->_posX + c2->_shape->GetRange(0) / 2;   bounds[3].y_end = c2->_posY + c2->_shape->GetRange(1) / 2;

	float t_min = 1.0f;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			float t_intersect = LineSegtoLineSeg(line_segments[i], bounds[j], j / 2);
			if (t_intersect < t_min) {
				t_min = t_intersect;
			}
		}
	}

	return (t_min != 1.0f);
}

// Check if object goes below ground level
// This is a hack for 3D games with 2D gameplay
// Where the only Z-plane collision is with the ground
bool CollisionManager::ObjecttoGround(GameObject * go)
{
	if (go->GetTag() == "Ground") return false;
	else {
		Collider * col = dynamic_cast<Collider*>(go->GetComponent(COMPONENT_TYPE::COLLIDER));
		if (!col) return false;
		else return (col->_posZ <= 0);
	}
}

bool CollisionManager::StaticSpheretoStaticPoint(GameObject * go_sphere, GameObject * go_static)
{
	Collider * c1 = dynamic_cast<Collider*>(go_sphere->GetComponent(COMPONENT_TYPE::COLLIDER));
	Collider * c2 = dynamic_cast<Collider*>(go_static->GetComponent(COMPONENT_TYPE::COLLIDER));

	float dist_sq = (c2->_posX - c1->_posX) * (c2->_posX - c1->_posX) + (c2->_posY - c1->_posY) * (c2->_posY - c1->_posY);
	return (c1->_shape->GetRange(0) * c1->_shape->GetRange(0) > dist_sq);
}

bool CollisionManager::StaticSpheretoDynamicPoint(GameObject * go_sphere, GameObject * go_dynamic)
{
	Collider * c1 = dynamic_cast<Collider*>(go_sphere->GetComponent(COMPONENT_TYPE::COLLIDER));
	Collider * c2 = dynamic_cast<Collider*>(go_dynamic->GetComponent(COMPONENT_TYPE::COLLIDER));

	// dynamic object must have rigid body component to perform motions
	RigidBody * body = dynamic_cast<RigidBody*>(go_dynamic->GetComponent(COMPONENT_TYPE::RIGID_BODY));
	if (!body) return false;

	Vector2D v, v_unit, ps_center;
	Vector2DSet(&v, body->_posX - body->_prevPosX, body->_posY - body->_prevPosY);
	Vector2DNormalize(&v_unit, &v);

	Vector2DSet(&ps_center, c1->_posX - body->_prevPosX, c1->_posY - body->_prevPosY);
	float m = Vector2DDotProduct(&v_unit, &ps_center);
	if (m < 0) return false;

	float range = c1->_shape->GetRange(0) + c2->_shape->GetRange(0);
	float nSquare = Vector2DSquareLength(&ps_center) - (m * m);
	float rSquare = (range * range);
	if (nSquare > rSquare) return false;

	float dist_ps_pe = Vector2DLength(&v);
	if (dist_ps_pe == 0) {
		return (rSquare > Vector2DSquareLength(&ps_center));
	}
	float s = sqrt(rSquare - nSquare);

	float t = (m - s) / dist_ps_pe;
	if (t < 0 || t > 1) {
		return false;
	}

	return true;
}

bool CollisionManager::DynamicSpheretoDynamicPoint(GameObject * go_sphere, GameObject * go_point)
{
	Collider * c1 = dynamic_cast<Collider*>(go_sphere->GetComponent(COMPONENT_TYPE::COLLIDER));
	Collider * c2 = dynamic_cast<Collider*>(go_point->GetComponent(COMPONENT_TYPE::COLLIDER));

	// dynamic object must have rigid body component to perform motions
	RigidBody * body1 = dynamic_cast<RigidBody*>(go_sphere->GetComponent(COMPONENT_TYPE::RIGID_BODY));
	RigidBody * body2 = dynamic_cast<RigidBody*>(go_point->GetComponent(COMPONENT_TYPE::RIGID_BODY));
	if (!body1 || !body2) return false;

	Vector2D v, v_unit, ps_center;
	Vector2DSet(&v, body2->_posX - body2->_prevPosX, body2->_posY - body2->_prevPosY);
	Vector2DSet(&v, v.x - (body1->_posX - body1->_prevPosX), v.y - (body1->_posY - body1->_prevPosY));
	Vector2DNormalize(&v_unit, &v);

	Vector2DSet(&ps_center, c1->_posX - body2->_prevPosX, c1->_posY - body2->_prevPosY);
	float m = Vector2DDotProduct(&v_unit, &ps_center);
	if (m < 0) return false;

	float range = c1->_shape->GetRange(0) + c2->_shape->GetRange(0);
	float nSquare = Vector2DSquareLength(&ps_center) - (m * m);
	float rSquare = (range * range);
	if (nSquare > rSquare) return false;

	float dist_ps_pe = Vector2DLength(&v);
	if (dist_ps_pe == 0) {
		return (rSquare > Vector2DSquareLength(&ps_center));
	}
	float s = sqrt(rSquare - nSquare);

	float t = (m - s) / dist_ps_pe;
	if (t < 0 || t > 1) {
		return false;
	}

	return true;
	/*
	LineSegment line1, line2;
	line1.x_start = body1->_prevPosX; line1.x_end = body1->_posX;
	line1.y_start = body1->_prevPosY; line1.y_end = body1->_posY;
	line2.x_start = body2->_prevPosX; line2.x_end = body2->_posX;
	line2.y_start = body2->_prevPosY; line2.y_end = body2->_posY;

	float cross_time = LineSegtoLineSeg(line1, line2, 2);
	if (cross_time < 0.0f || cross_time > 1.0f) return false;

	float range = c1->_shape->GetRange(0) + c2->_shape->GetRange(0);
	float sphere_intersect_x = line1.x_start + cross_time * (line1.x_end - line1.x_start);
	float sphere_intersect_y = line1.y_start + cross_time * (line1.y_end - line1.y_start);
	float point_intersect_x =  line2.x_start + cross_time * (line2.x_end - line2.x_start);
	float point_intersect_y =  line2.y_start + cross_time * (line2.y_end - line2.y_start);

	float dist = (sphere_intersect_x - point_intersect_x) * (sphere_intersect_x - point_intersect_x) + (sphere_intersect_y - point_intersect_y) * (sphere_intersect_y - point_intersect_y);
	return (dist <= (range * range));
	*/

}

// 0 means bound is parallel to x axis
// 1 means bound is parallel to y axis
// 2 means no axis bound
float CollisionManager::LineSegtoLineSeg(LineSegment& line, LineSegment& bound, int axis)
{
	float t = 1.0f;
	if (axis == 0) {
		if (line.x_start != line.x_end) {
			float intersect_t = (bound.x_start - line.x_start) / (line.x_end - line.x_start);
			if (intersect_t <= 1 && intersect_t >= 0) {
				float y_intersect = line.y_start + (line.y_end - line.y_start) * t;
				if ((y_intersect - bound.y_start) * (y_intersect - bound.y_end) <= 0) {
					//std::cout << intersect_t << ", " << y_intersect << ", " << bound.y_start << ", " << bound.y_end << std::endl;
					t = intersect_t;
				}
			}
		}
	}
	else if (axis == 1) {
		if (line.y_start != line.y_end) {
			float intersect_t = (bound.y_start - line.y_start) / (line.y_end - line.y_start);
			if (intersect_t <= 1 && intersect_t >= 0) {
				float x_intersect = line.x_start + (line.x_end - line.x_start) * t;
				if ((x_intersect - bound.x_start) * (x_intersect - bound.x_end) <= 0) {
					//std::cout << intersect_t << ", " << x_intersect << ", " << bound.x_start << ", " << bound.x_end << std::endl;
					t = intersect_t;
				}
			}
		}
	}
	else if (axis == 2) {

	}
	
	return t;
}

void CollisionManager::Enqueue(GameObject * go1, GameObject * go2)
{
	Collision c(go1, go2);
	_collisions.push(c);
}

void CollisionManager::ResolveCollisions()
{
	while (!_collisions.empty()) {
		// Pass collisions to each object
		Collision collision = _collisions.front();

		if (collision.second) {
			OnCollision event1(collision.second);
			collision.first->ReceiveEvent(&event1);

			OnCollision event2(collision.first);
			collision.second->ReceiveEvent(&event2);
		}
		else {
			OnCollision event(0);
			collision.first->ReceiveEvent(&event);
		}
		_collisions.pop();
	}
}
