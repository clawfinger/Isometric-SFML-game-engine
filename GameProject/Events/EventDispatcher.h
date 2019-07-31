#pragma once
#include <unordered_map>
#include "Subscription.h"
#include "../Utils/Meta.h"

class EventDispatcher
{
public:
	EventDispatcher();
	~EventDispatcher();
	void subscribe(const std::string& eventName, Observer* observer);
	void unsubscribe(const std::string& eventName, Observer* observer);

	template<typename T, typename... Args>
	void dispatch(Args... args);

private:
	void dispatch(IEvent* event);


private:
	std::unordered_map<std::string, Subscription> m_subscriptions;
	std::unordered_map<std::string, IEvent*> m_eventContainer;
};

template<typename T, typename... Args>
void EventDispatcher::dispatch(Args... args)
{
	T event(args...);
	dispatch(&event);
}

REGISTER_TYPENAME(EventDispatcher)
