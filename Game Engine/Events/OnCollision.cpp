#include "OnCollision.h"

OnCollision::OnCollision(GameObject * target) : Event(EVENT_TYPE::ON_COLLISION), _target(target)
{
}

/*
OnCollision::OnCollision(bool ground_collision): Event(EVENT_TYPE::ON_COLLISION), _groundCollision(ground_collision)
{
}
*/

OnCollision::~OnCollision()
{
}
