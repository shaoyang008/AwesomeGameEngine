#include "Transform.h"



Transform::Transform(): Component(COMPONENT_TYPE::TRANSFORM), _posX(0.0), _posY(0.0)
{
	offset = new SDL_Rect;
	Update();
}

Transform::Transform(float x, float y): Component(COMPONENT_TYPE::TRANSFORM), _posX(x), _posY(y)
{
	offset = new SDL_Rect;
	Update();
}


Transform::~Transform()
{
	delete offset;
}

void Transform::Update() 
{
	offset->x = _posX;
	offset->y = _posY;
}

void Transform::Serialize(std::string data)
{
	size_t xpos = data.find_first_of(',');
	size_t ypos = data.find_first_not_of(' ', xpos + 1);

	_posX = std::stof(data.substr(0, xpos));
	_posY = std::stof(data.substr(ypos));
	std::cout << "Transform is " << _posX << ", " << _posY << std::endl;
}