#include "Projectile.h"
#include "../GameStateManager.h"
#include "../Events/PlayerHit.h"

#define FLY_SPEED 30.0f
#define LIFETIME 1000.0f

extern GameStateManager * pMgr;


Projectile::Projectile(): Component(COMPONENT_TYPE::PROJECTILE), _lifetime(0)
{
}


Projectile::~Projectile()
{
}

void Projectile::Update()
{
	++_lifetime;
	if (_lifetime > LIFETIME) _owner->Deactivate();
}

void Projectile::Serialize(json data)
{

}

void Projectile::Initialize()
{
	if (_shooter) {
		Transform * transform = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));
		Transform * o_transform = dynamic_cast<Transform*>(_shooter->GetComponent(COMPONENT_TYPE::TRANSFORM));
		transform->_translateX = o_transform->_translateX;
		transform->_translateY = o_transform->_translateY;
		transform->_rotateZ = o_transform->_rotateZ;
	}
	RigidBody * body = dynamic_cast<RigidBody*>(_owner->GetComponent(COMPONENT_TYPE::RIGID_BODY));
	body->_vel = FLY_SPEED;

	_lifetime = 0;
}

void Projectile::HandleEvent(Event * e)
{
	if (e->GetType() == EVENT_TYPE::ON_COLLISION) {
		OnCollision * oc = dynamic_cast<OnCollision*>(e);
		if (oc->_target && oc->_target->GetTag() == "Player") {
			Event * p = new PlayerHit;
			pMgr->_eventManager->Enque(p);
			_owner->Deactivate();
		}
	}
}

void Projectile::SetShooter(std::string shooter_tag)
{
	_shooter = pMgr->_gameObjectManager->_tagObjects.FindValueByKey(shooter_tag);
}