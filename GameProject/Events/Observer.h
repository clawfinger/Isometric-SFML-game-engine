#pragma once
#include <unordered_map>
#include <string>
#include <functional>
#include <vector>
#include "../Utils/Logger.h"
#include "Events.h"

//class IEvent;
//class Observer
//{
//public:
//	virtual ~Observer() {};
//	virtual void notify(IEvent* event) = 0;
//};

class Observer
{
public:
	virtual ~Observer() {};
	void notify(IEvent* event) const
	{
		auto it = m_callbacks.find(event->name());
		if (it != m_callbacks.end())
		{
			for (auto callback : it->second)
				callback(event);
		}
		else
			Logger::instance().log("Cannot find callback for event " + event->name());
	}

	void registerCallBack(const std::string& eventName, std::function<void(IEvent*)> f)
	{
		m_callbacks[eventName].push_back(f);
	}

private:
	typedef std::vector<std::function<void(IEvent*)>> callBackVector;
	std::unordered_map < std::string, callBackVector> m_callbacks;
};

