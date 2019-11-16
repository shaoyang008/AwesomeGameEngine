#include "DelayMove.h"



DelayMove::DelayMove(): Event(EVENT_TYPE::DELAY_MOVE), _elapsedTime(0.0f), _queued(false)
{
}

DelayMove::DelayMove(float time): Event(EVENT_TYPE::DELAY_MOVE), _elapsedTime(time), _queued(false)
{

}


DelayMove::~DelayMove()
{
}
