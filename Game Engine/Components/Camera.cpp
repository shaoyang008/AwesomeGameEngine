#include "Camera.h"
#include "../GameStateManager.h"

extern GameStateManager *pMgr;


Camera::Camera(): Component(COMPONENT_TYPE::CAMERA), _targetTag(""), _targetPosition(vec3(0, 0, 0))
{
}


Camera::~Camera()
{
}

void Camera::Update()
{
	if (!_target) {
		return;
	}

	Transform * transform = dynamic_cast<Transform*>(_target->GetComponent(COMPONENT_TYPE::TRANSFORM));
	_targetPosition.x = transform->_translateX;
	_targetPosition.y = transform->_translateY;
	_targetPosition.z = transform->_translateZ;
}

void Camera::Serialize(json data)
{
	_targetTag = data["Target"].get<std::string>();

	_ry = data["RY"].get<float>();
	_back = data["Back"].get<float>();
	_front = data["Front"].get<float>();

	_tile = data["Tilt"].get<float>();
	_spin = data["Spin"].get<float>();

	_position.x = data["Position"][0].get<float>();
	_position.y = data["Position"][1].get<float>();
	_position.z = data["Position"][2].get<float>();
}

void Camera::Initialize()
{
	// Set camera to follow target object
	if (_targetTag == "") return;

	_target = pMgr->_gameObjectManager->_tagObjects.FindValueByKey(_targetTag);
	
	Transform * transform = dynamic_cast<Transform*>(_target->GetComponent(COMPONENT_TYPE::TRANSFORM));
	_targetPosition.x = transform->_translateX;
	_targetPosition.y = transform->_translateY;
	_targetPosition.z = transform->_translateZ;
}

