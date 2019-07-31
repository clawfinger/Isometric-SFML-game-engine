#pragma once
#include <unordered_map>
#include "Factory.h"
#include "../Utils/Logger.h"
#include "../Utils/Meta.h"


class DiContainer
{
public:
	template <typename ReturnT>
	void registerClass(typename Factory<ReturnT>::constructingFunction function, FactoryType type = FactoryType::singleInstance);

	template<typename ReturnT>
	std::shared_ptr<ReturnT> get() const;
private:
	std::unordered_map<std::string, IFactory*> m_factories;
};

template<typename ReturnT>
void DiContainer::registerClass(typename Factory<ReturnT>::constructingFunction function, FactoryType type)
{
	std::string name = typeName<ReturnT>();
	if (name.empty())
		LOG("ERROR: Registering class without REGISTER TYPENAME macro defined!");
	m_factories[name] = new Factory<ReturnT>(function, type);
};

template<typename ReturnT>
inline std::shared_ptr<ReturnT> DiContainer::get() const
{
	auto factory = m_factories.find(typeName<ReturnT>());
	if (factory != m_factories.end())
	{
		return dynamic_cast<Factory<ReturnT>*>(factory->second)->create(*this);
	}
	else
		return nullptr;
};