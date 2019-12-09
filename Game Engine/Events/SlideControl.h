#pragma once
#include "Event.h"

class SlideControl : public Event
{
public:
	enum TYPE {
		NEXT,
		SHOW,
		CLOSE
	};

	SlideControl(TYPE);
	~SlideControl();

	int _control;
};

