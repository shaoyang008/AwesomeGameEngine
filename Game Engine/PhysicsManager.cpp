#include "PhysicsManager.h"
#include "GameStateManager.h"

extern GameStateManager *pMgr;


PhysicsManager::PhysicsManager()
{
}


PhysicsManager::~PhysicsManager()
{
}

void PhysicsManager::PhysicsUpdate()
{
	for (int i = 0; i < pMgr->_gameObjectManager->_objects.size(); ++i) {
		Component * body = pMgr->_gameObjectManager->_objects[i]->GetComponent(COMPONENT_TYPE::RIGID_BODY);
		if (body) {
			dynamic_cast<RigidBody*>(body)->Integrate(GLOBAL_GRAVITY, pMgr->_framerateManager->_frameTime/1000.0f);
		}
	}
}
