#include "OnCollision.h"



OnCollision::OnCollision(bool ground_collision): Event(EVENT_TYPE::ON_COLLISION), _groundCollision(ground_collision)
{
}


OnCollision::~OnCollision()
{
}
