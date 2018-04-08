#pragma once
#include <unordered_map>
#include "Factory.h"

class DiContainer
{
public:
	template <typename ResultT>
	void registerClass(constructingFunction function);

	template<typename ResultT>
	ResultT* get();
private:
	std::unordered_map<std::string, IFactory*> m_factories;
};

template<typename ResultT>
inline void DiContainer::registerClass(constructingFunction function)
{
}

template<typename ResultT>
inline ResultT * DiContainer::get()
{
	return NULL;
}
