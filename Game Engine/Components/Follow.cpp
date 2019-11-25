#include "Follow.h"
#include "Transform.h"
#include "../GameStateManager.h"

extern GameStateManager * pMgr;

Follow::Follow(): Component(COMPONENT_TYPE::FOLLOW), _distanceX(0.0f), _distanceY(0.0f)
{
}


Follow::~Follow()
{
}

void Follow::Update()
{
	Transform * transform = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));
	Transform * follow_transform = dynamic_cast<Transform*>(_followObject->GetComponent(COMPONENT_TYPE::TRANSFORM));

	transform->_translateX = follow_transform->_translateX + _distanceX;
	transform->_translateY = follow_transform->_translateY + _distanceY;
}

void Follow::Serialize(json data)
{
	_followTag = data["Tag"].get<std::string>();

	_distanceX = data["DistanceX"].get<float>();
	_distanceY = data["DistanceY"].get<float>();
}

void Follow::Initialize()
{
	_followObject = pMgr->_gameObjectManager->_tagObjects.FindValueByKey(_followTag);
}