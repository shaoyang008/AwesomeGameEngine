#include "Collider.h"



Collider::Collider(): Component(COMPONENT_TYPE::COLLIDER)
{
}

 
Collider::~Collider()
{
}

void Collider::Update()
{
	Transform * transform = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));
	_posX = transform->_translateX;
	_posY = transform->_translateY;
	_posZ = transform->_translateZ;
}

void Collider::Serialize(json data)
{
	_height = data["Height"].get<float>();
	_width  = data["Width"].get<float>();
	_length = data["Length"].get<float>();
}
