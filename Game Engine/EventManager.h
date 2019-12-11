/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: EventManager.h
Purpose: Enque and resolve events
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

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

