#pragma once
#include <memory>
#include "ConstructingFunctions.h"

enum class FactoryType
{
	singleInstance,
	multiInstance
};

class IFactory
{
public:
	virtual ~IFactory() {};
};

template <typename ReturnT>
class Factory : public IFactory
{
public:
	using constructingFunction = ReturnT*(*)(const DiContainer& cont);
	~Factory() {};
	Factory(constructingFunction function, FactoryType type) :
		m_function(function), m_type(type), m_instance(nullptr) {};

	std::shared_ptr<ReturnT> create(const DiContainer& container)
	{
		if (m_type == FactoryType::singleInstance)
		{
			if (m_instance == nullptr)
				m_instance = std::shared_ptr<ReturnT>(m_function(container));
			return m_instance;
		}
		if (m_type == FactoryType::multiInstance)
			return std::shared_ptr<ReturnT>(m_function(container));
		return m_instance;
	}
private:
	constructingFunction m_function;
	FactoryType m_type;
	std::shared_ptr<ReturnT> m_instance;
};