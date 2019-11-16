#include "ResetPlayer.h"
#include "../GameStateManager.h"

extern GameStateManager *pMgr;


ResetPlayer::ResetPlayer(): Component(COMPONENT_TYPE::RESET_PLAYER), _posX(0.0f), _posY(0.0f)
{
}


ResetPlayer::~ResetPlayer()
{
}

void ResetPlayer::Update()
{

}
void ResetPlayer::Serialize(json data)
{

}

void ResetPlayer::Initialize()
{
	Transform *t = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));
	_posX = t->_posX;
	_posY = t->_posY;
}

void ResetPlayer::HandleEvent(Event * e)
{
	if (e->GetType() == EVENT_TYPE::ON_COLLISION) {
		Transform *t = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));
		t->_posX = _posX;
		t->_posY = _posY;

		RigidBody *r = dynamic_cast<RigidBody*>(_owner->GetComponent(COMPONENT_TYPE::RIGID_BODY));
		r->Stop();
	}
}