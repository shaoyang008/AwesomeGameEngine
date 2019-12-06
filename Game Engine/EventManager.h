#pragma once
#include <unordered_map>
#include <vector>
#include "GameObject.h"
#include "Events/Event.h"
#include <queue>

class EventManager {
public:
	EventManager();
	~EventManager();

	void Enque(Event*);
	void ResolveEvents();
	void SubscribeEvent(EVENT_TYPE, GameObject*);
	void ClearSubscribe();

private:
	std::queue<Event*> _eventQueues[2];
	int _queueIndex, _nextQueueIndex;
	std::unordered_map<EVENT_TYPE, std::vector<GameObject*>> _subscribers;
};

