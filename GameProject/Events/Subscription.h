#pragma once
#include "Observer.h"
#include <vector>

class Subscription : public Observer
{
public:
	Subscription();
	~Subscription();
	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);
	void broadcast(IEvent* event);
private:
	std::vector<Observer*> m_observers;
};

