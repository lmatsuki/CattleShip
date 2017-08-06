#pragma once

#include "EventsEnum.h"

class Observer
{
public:
	virtual ~Observer() {};
	virtual void onNotify(const EventsEnum event) = 0;
};