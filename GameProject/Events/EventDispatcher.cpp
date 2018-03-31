#include "stdafx.h"
#include "EventDispatcher.h"
#include "Events.h"
#include <iostream>

EventDispatcher::EventDispatcher()
{
}


EventDispatcher::~EventDispatcher()
{
}

void EventDispatcher::subscribe(std::string eventName, Observer * observer)
{
	m_subscriptions[eventName].addObserver(observer);
}

void EventDispatcher::unsubscribe(std::string eventName, Observer * observer)
{
	auto subscription = m_subscriptions.find(eventName);
	if (subscription != m_subscriptions.end())
	{
		subscription->second.removeObserver(observer);
	}
	else
		std::cout << "No subscribers for " << eventName << std::endl;
}

void EventDispatcher::dispatch(IEvent * event)
{
	auto subscription = m_subscriptions.find(event->name());
	if (subscription != m_subscriptions.end())
	{
		subscription->second.broadcast(event);
	}
}
