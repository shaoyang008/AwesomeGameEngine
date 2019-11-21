#include "DelayMove.h"
#include "../GameStateManager.h"

extern GameStateManager *pMgr;


DelayMove::DelayMove(): Event(EVENT_TYPE::DELAY_MOVE), _elapsedTime(0.0f), _queued(false)
{
}


DelayMove::~DelayMove()
{
}

bool DelayMove::ShouldTrigger()
{
	if (_elapsedTime > DELAY_TIME) return true;
	else {
		_elapsedTime += pMgr->_framerateManager->_frameTime / 1000.0f;
		return false;
	}
}
