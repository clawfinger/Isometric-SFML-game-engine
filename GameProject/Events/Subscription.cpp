#include "stdafx.h"
#include "Subscription.h"
#include "../Utils/Logger.h"
#include "../Events/Events.h"
#include <algorithm>
#include <string>

Subscription::Subscription()
{
}


Subscription::~Subscription()
{
}

void Subscription::addObserver(Observer * observer)
{
	if ((std::find_if(m_observers.begin(), m_observers.end(),
		[&](Observer* obs)->bool {return observer == obs; }) == m_observers.end()))
	{
		m_observers.push_back(observer);
	}
	else
	{
		Logger::instance().log("Observer " + std::to_string(int(observer)) + " already in subscription list");
	}
}

void Subscription::removeObserver(Observer * observer)
{
	auto toRemove = (std::find_if(m_observers.begin(), m_observers.end(),
		[&](Observer* obs)->bool {return observer == obs; }));
	if (toRemove != m_observers.end())
	{
		m_observers.erase(toRemove);
	}
	else
	{
		Logger::instance().log("Observer " + std::to_string(int(observer)) + " not found in subscribsions");

	}
}

void Subscription::broadcast(IEvent * event)
{
	for (auto& observer : m_observers)
	{
		observer->notify(event);
	}
	delete event;
}
