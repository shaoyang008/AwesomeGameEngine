#pragma once
#include "Event.h"

class SlideControl : public Event
{
public:
	enum {
		NEXT,
		SHOW,
		CLOSE
	};

	SlideControl();
	~SlideControl();

	int _control;
};

