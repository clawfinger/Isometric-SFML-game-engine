#include "stdafx.h"
#include "Subscription.h"
#include <algorithm>
#include <iostream>

Subscription::Subscription()
{
}


Subscription::~Subscription()
{
}

void Subscription::addObserver(Observer * observer)
{
	if ((std::find_if(m_observers.begin(), m_observers.end(),
		[&](Observer* obs)->bool {observer == obs; }) != m_observers.end()))
	{
		m_observers.push_back(observer);
	}
	else
	{
		std::cout << "Observer " << observer << " already in subscription list" << std::endl;
	}
}

void Subscription::removeObserver(Observer * observer)
{
	auto toRemove = (std::find_if(m_observers.begin(), m_observers.end(),
		[&](Observer* obs)->bool {observer == obs; }));
	if (toRemove != m_observers.end())
	{
		m_observers.erase(toRemove);
	}
	else
	{
		std::cout << "Observer " << observer << " already removed" << std::endl;
	}
}

void Subscription::broadcast(IEvent * event)
{
	for (auto& observer : m_observers)
	{
		observer->notify(event);
	}
}
