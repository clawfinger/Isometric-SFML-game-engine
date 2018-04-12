#pragma once
#include <unordered_map>
#include "Subscription.h"
#include "../Utils/Meta.h"

class EventDispatcher
{
public:
	EventDispatcher();
	~EventDispatcher();
	void subscribe(std::string eventName, Observer* observer);
	void unsubscribe(std::string eventName, Observer* observer);
	void dispatch(IEvent* event);
private:
	std::unordered_map<std::string, Subscription> m_subscriptions;
};
REGISTER_TYPENAME(EventDispatcher)
