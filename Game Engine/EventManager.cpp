#include "EventManager.h"
#include "../GameStateManager.h"

extern GameStateManager *pMgr;


EventManager::EventManager() : _queueIndex(0), _nextQueueIndex(1)
{
}


EventManager::~EventManager()
{
}

void EventManager::Enque(Event* e)
{
	_eventQueues[_nextQueueIndex].push(e);
}

void EventManager::ResolveEvents()
{
	while (!_eventQueues[_queueIndex].empty()) {
		Event * e = _eventQueues[_queueIndex].front();
		if (e->ShouldTrigger()) {
			if (_subscribers.find(e->GetType()) == _subscribers.end()) {
				// Not registered as subscription event
				// broadcast to all game objects
				for (int i = 0; i < pMgr->_gameObjectManager->_objects.size(); ++i) {
					pMgr->_gameObjectManager->_objects[i]->ReceiveEvent(e);
				}
			}
			else {
				// Only pass event to subscribers
				for (int i = 0; i < _subscribers[e->GetType()].size(); ++i) {
					_subscribers[e->GetType()][i]->ReceiveEvent(e);
				}
			}
			delete e;
		}
		else {
			Enque(e);
		}
		_eventQueues[_queueIndex].pop();
	}
	_queueIndex = _nextQueueIndex;
	_nextQueueIndex = (_nextQueueIndex + 1) % 2;
}

void EventManager::SubscribeEvent(EVENT_TYPE type, GameObject * object)
{
	_subscribers[type].push_back(object);
}
