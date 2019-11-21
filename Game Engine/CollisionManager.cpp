#include "CollisionManager.h"
#include "GameStateManager.h"

extern GameStateManager *pMgr;


CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}

void CollisionManager::CheckCollisions()
{
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
			else {
				if (StaticAABBtoAABB(obj1, obj2)) {
					// std::cout << obj1->GetTag() << " collides with " << obj2->GetTag() << std::endl;
					Enqueue(obj1, obj2);
				}
			}
		}
	}
}

bool CollisionManager::StaticAABBtoAABB(GameObject * g1, GameObject * g2)
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

// Check if object goes below ground level
// This is a hack for 3D games with 2D gameplay
// Where the only Z-plane collision is with the ground
bool CollisionManager::StaticAABBtoGround(GameObject * go)
{
	Collider * col = dynamic_cast<Collider*>(go->GetComponent(COMPONENT_TYPE::COLLIDER));
	if (!col) return false;
	else return (col->_posZ < 0);
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
			event = new OnCollision();
			collision->_go1->ReceiveEvent(event);
			collision->_go2->ReceiveEvent(event);
		}
		else {
			event = new OnCollision(true);
			collision->_go1->ReceiveEvent(event);
		}
		_collisions.pop();
		delete collision;
		delete event;
	}
}
