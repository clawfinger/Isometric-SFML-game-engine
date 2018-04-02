#pragma once
#include <string>

class ComponentBase
{
	ComponentBase(const std::string& componentName) :
		m_name(componentName){};
	virtual ~ComponentBase() {};
private:
	std::string m_name;
};