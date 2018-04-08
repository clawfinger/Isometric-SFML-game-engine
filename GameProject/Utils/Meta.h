#pragma once
#include <string>

template<class T>
static std::string typeName()
{
	return std::string("DEFAULT");
}

#define REGISTER_TYPENAME(name) \
	template<>\
	std::string typeName<name>()\
	{\
		return std::string(#name);\
	}
