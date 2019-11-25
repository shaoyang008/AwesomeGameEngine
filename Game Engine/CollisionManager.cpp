#include "CollisionManager.h"
#include "GameStateManager.h"

extern GameStateManager *pMgr;


CollisionManager::CollisionManager()
{
	for (int i = 0; i < static_cast<int>(COLLIDER_TYPE::count); ++i) {
		for (int j = 0; j < static_cast<int>(COLLIDER_TYPE::count); ++j) {
			_collisionTests[i][j] = &CollisionManager::NotImplemented;
		}
	}
	// All collision methods between different types of objects
	// Types are defined in COLLIDER_TYPE
	// 0: static aabb			1: dynamic aabb
	// 2: static sphere	(WIP)	3: dynamic sphere (WIP)
	_collisionTests[0][0] = &CollisionManager::StaticAABBtoStaticAABB;
	_collisionTests[0][1] = &CollisionManager::StaticAABBtoDynamicAABB;
	_collisionTests[1][0] = &CollisionManager::StaticAABBtoDynamicAABB;
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
		if (obj1->GetTag() == "Ground") continue;
		else {
			if (StaticAABBtoGround(obj1)) {
				// std::cout << obj1->GetTag() << " hits the ground." << std::endl;
				Enqueue(obj1, 0);
			}
		}
		for (int j = i + 1; j < pMgr->_gameObjectManager->_objects.size(); ++j) {
			GameObject * obj2 = pMgr->_gameObjectManager->_objects[j];
			if (obj2->GetTag() == "Ground") continue;
			else if(obj1->GetTag() == "Player") {
				if (StaticAABBtoDynamicAABB(obj1, obj2)) {
					// std::cout << obj1->GetTag() << " collides with " << obj2->GetTag() << std::endl;
					Enqueue(obj1, obj2);
				}
			}
			else if (obj2->GetTag() == "Player") {
				if (StaticAABBtoDynamicAABB(obj2, obj1)) {
					// std::cout << obj1->GetTag() << " collides with " << obj2->GetTag() << std::endl;
					Enqueue(obj1, obj2);
				}
			}
		}
	}
}

bool CollisionManager::StaticAABBtoStaticAABB(GameObject * g1, GameObject * g2)
{
	Collider * c1 = dynamic_cast<Collider*>(g1->GetComponent(COMPONENT_TYPE::COLLIDER));
	Collider * c2 = dynamic_cast<Collider*>(g2->GetComponent(COMPONENT_TYPE::COLLIDER));
	if(!c1 || !c2) return false;

	return (!(
		(c1->_posX - c1->_width / 2 > c2->_posX + c2->_width / 2) ||
		(c1->_posX + c1->_width / 2 < c2->_posX - c2->_width / 2) ||
		(c1->_posY - c1->_length / 2 > c2->_posY + c2->_length / 2) ||
		(c1->_posY + c1->_length / 2 < c2->_posY - c2->_length / 2)
	));
}

bool CollisionManager::StaticAABBtoDynamicAABB(GameObject * go_dynamic, GameObject * go_static)
{
	Collider * c1 = dynamic_cast<Collider*>(go_dynamic->GetComponent(COMPONENT_TYPE::COLLIDER));
	Collider * c2 = dynamic_cast<Collider*>(go_static->GetComponent(COMPONENT_TYPE::COLLIDER));
	if (!c1 || !c2) return false;

	// dynamic object must have rigid body component to perform motions
	RigidBody * body = dynamic_cast<RigidBody*>(go_dynamic->GetComponent(COMPONENT_TYPE::RIGID_BODY));
	if (!body) return false;

	std::vector<float> intersect_time;

	// Calculate four points of previous frame
	LineSegment line_segments[4];
	line_segments[0].x_start = body->_prevPosX - c1->_width / 2; line_segments[0].y_start = body->_prevPosY - c1->_length / 2;
	line_segments[1].x_start = body->_prevPosX + c1->_width / 2; line_segments[1].y_start = body->_prevPosY - c1->_length / 2;
	line_segments[2].x_start = body->_prevPosX - c1->_width / 2; line_segments[2].y_start = body->_prevPosY + c1->_length / 2;
	line_segments[3].x_start = body->_prevPosX + c1->_width / 2; line_segments[3].y_start = body->_prevPosY + c1->_length / 2;

	// Calculate four points of current frame
	line_segments[0].x_end = body->_posX - c1->_width / 2; line_segments[0].y_end = body->_posY - c1->_length / 2;
	line_segments[1].x_end = body->_posX + c1->_width / 2; line_segments[1].y_end = body->_posY - c1->_length / 2;
	line_segments[2].x_end = body->_posX - c1->_width / 2; line_segments[2].y_end = body->_posY + c1->_length / 2;
	line_segments[3].x_end = body->_posX + c1->_width / 2; line_segments[3].y_end = body->_posY + c1->_length / 2;

	// Calculate four bounds of static object
	LineSegment bounds[4];
	// left bound
	bounds[0].x_start = c2->_posX - c2->_width / 2; bounds[0].y_start = c2->_posY - c2->_length / 2;
	bounds[0].x_end = c2->_posX - c2->_width / 2;   bounds[0].y_end = c2->_posY + c2->_length / 2;
	// right bound
	bounds[1].x_start = c2->_posX + c2->_width / 2; bounds[1].y_start = c2->_posY - c2->_length / 2;
	bounds[1].x_end = c2->_posX + c2->_width / 2;   bounds[1].y_end = c2->_posY + c2->_length / 2;
	// lower bound
	bounds[2].x_start = c2->_posX - c2->_width / 2; bounds[2].y_start = c2->_posY - c2->_length / 2;
	bounds[2].x_end = c2->_posX + c2->_width / 2;   bounds[2].y_end = c2->_posY - c2->_length / 2;
	// upper bound
	bounds[3].x_start = c2->_posX - c2->_width / 2; bounds[3].y_start = c2->_posY + c2->_length / 2;
	bounds[3].x_end = c2->_posX + c2->_width / 2;   bounds[3].y_end = c2->_posY + c2->_length / 2;

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
bool CollisionManager::StaticAABBtoGround(GameObject * go)
{
	Collider * col = dynamic_cast<Collider*>(go->GetComponent(COMPONENT_TYPE::COLLIDER));
	if (!col) return false;
	else return (col->_posZ <= 0);
}

// 0 means bound is parallel to x axis
// 1 means bound is parallel to y axis
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
	
	return t;
}

void CollisionManager::Enqueue(GameObject * go1, GameObject * go2)
{
	Collision * c = new Collision(go1, go2);
	_collisions.push(c);
}

void CollisionManager::ResolveCollisions()
{
	while (!_collisions.empty()) {
		// Pass collisions to each object
		Collision * collision = _collisions.front();
		Event* event;

		if (collision->_go2) {
			event = new OnCollision(false);
			collision->_go1->ReceiveEvent(event);
			collision->_go2->ReceiveEvent(event);
		}
		else {
			event = new OnCollision();
			collision->_go1->ReceiveEvent(event);
		}
		_collisions.pop();
		delete collision;
		delete event;
	}
}
