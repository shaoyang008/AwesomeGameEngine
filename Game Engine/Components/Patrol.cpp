#include "Patrol.h"
#include "../GameStateManager.h"

extern GameStateManager *pMgr;

Patrol::Patrol(): Component(COMPONENT_TYPE::PATROL), _speedX(0.0), _speedY(0.0), _direction(true), _maxTime(1000.0), _time(0.0)
{
}


Patrol::~Patrol()
{
}

void Patrol::Update()
{
	Transform * t = dynamic_cast<Transform*>(pOwner->GetComponent(COMPONENT_TYPE::TRANSFORM));
	if (_time > _maxTime) {
		_direction = !_direction;
		_time = 0;
	}
	else {
		if (_direction) {
			t->_posX += _speedX;
			t->_posY += _speedY;
		}
		else {
			t->_posX -= _speedX;
			t->_posY -= _speedY;
		}
		_time += pMgr->pFM->frame_time;
	}
}

void Patrol::Serialize(std::string data)
{
	size_t speed_pos = data.find_first_of(':');
	size_t split_pos = data.find_first_of('/', speed_pos);

	std::string speed = data.substr(speed_pos + 1, split_pos - speed_pos - 1);
	size_t speed_xpos = speed.find_first_of(',');
	size_t speed_ypos = speed.find_first_not_of(' ', speed_xpos + 1);

	_speedX = std::stof(speed.substr(0, speed_xpos));
	_speedY = std::stof(speed.substr(speed_ypos));
	std::cout << "Speed is " << _speedX << ", " << _speedY << std::endl;

	size_t time_pos = data.find_first_of(':', split_pos);
	_maxTime = std::stof(data.substr(time_pos + 1));
}
