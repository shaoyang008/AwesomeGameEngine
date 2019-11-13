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
	_posX = transform->_posX;
	_posY = transform->_posY;
}

void Collider::Serialize(json data)
{
	_height  = std::stof(data["Height"].get<std::string>());
	_width   = std::stof(data["Width"].get<std::string>());
}
