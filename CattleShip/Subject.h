#pragma once

#include <vector>
#include "Observer.h"

class Subject
{
public:
	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);

protected:
	void notify(const EventsEnum event);

private:
	std::vector<Observer> observers;
};