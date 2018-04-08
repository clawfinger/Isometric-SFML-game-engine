#pragma once
#include "ConstructingFunctions.h"

class IFactory
{
public:
	virtual ~IFactory() {};
};

template<typename ResultT>
class Factory : public IFactory
{
public:
	using constructingFunction = ResultT*(*)(const DiContainer& cont);
	Factory(constructingFunction function) : m_function(function) {};
	ResultT* create(const DiContainer& cont)
	{
		return m_function(cont);
	}
private:
	constructingFunction m_function;
};