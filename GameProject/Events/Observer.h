#pragma once
class IEvent;
class Observer
{
public:
	virtual ~Observer() {};
	virtual void notify(IEvent* event) = 0;
};