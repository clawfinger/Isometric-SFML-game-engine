#pragma once
#include "ConstructingFunctions.h"

class IFactory
{
public:
	virtual ~IFactory() {};
};

class Factory : public IFactory
{

};