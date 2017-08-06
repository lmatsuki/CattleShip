#include "Subject.h"

void Subject::addObserver(Observer * observer)
{
	//observers.push_back(*observer);
}

void Subject::removeObserver(Observer * observer)
{
	int observerCount = observers.size();
	for (int i = 0; i < observerCount; i++)
	{
		if (&observers.at(i) == observer)
		{
			observers.erase(observers.begin() + i);
		}
	}
}

void Subject::notify(const EventsEnum event)
{
	int observerCount = observers.size();
	for (int i = 0; i < observerCount; i++)
		observers.at(i).onNotify(event);
}
