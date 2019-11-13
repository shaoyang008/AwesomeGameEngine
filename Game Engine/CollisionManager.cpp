#include "CollisionManager.h"
#include "GameStateManager.h"

extern GameStateManager *pMgr;


CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}

void CollisionManager::PlayerCollision(std::string player_tag)
{
	GameObject * player = *(pMgr->_gameObjectManager->_tagObjects.FindValueByKey(player_tag));
	for (int i = 0; i < pMgr->_gameObjectManager->_objects.size(); ++i) {
		GameObject * target = pMgr->_gameObjectManager->_objects[i];
		if (target->GetTag() == player_tag) continue;
		else {
			StaticAABBtoAABB(player, target);
		}
	}
}

bool CollisionManager::StaticAABBtoAABB(GameObject * g1, GameObject * g2)
{
	Collider * c1 = dynamic_cast<Collider*>(g1->GetComponent(COMPONENT_TYPE::COLLIDER));
	Collider * c2 = dynamic_cast<Collider*>(g2->GetComponent(COMPONENT_TYPE::COLLIDER));
	if(!c1 || !c2) return false;

	if (!(
		(c1->_posX > c2->_posX + c2->_width) ||
		(c1->_posX + c1->_width < c2->_posX) ||
		(c1->_posY > c2->_posY + c2->_height) ||
		(c1->_posY + c1->_height < c2->_posY)
		)) {
		std::cout << g1->GetTag() << " collides with " << g2->GetTag() << std::endl;
		return true;
	}
	else return false;
}
