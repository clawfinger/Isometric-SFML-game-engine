#pragma once
#include "../Utils/Meta.h"

class IEvent
{
public:
	virtual std::string name() = 0;
	virtual ~IEvent() {};
};