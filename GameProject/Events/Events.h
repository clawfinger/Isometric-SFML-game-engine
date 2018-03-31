#pragma once
#include "../Meta.h"

class IEvent
{
public:
	virtual std::string name() = 0;
	virtual ~IEvent() {};
};