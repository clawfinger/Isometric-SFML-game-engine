#pragma once
#include <string>
template <typename T>
class TypeNameResolver
{
	std::string typeName() { return "Default"; };
};

#define REGISTER_TYPENAME(NAME) \
template<> \
class TypeNameResolver<NAME> \
{ \
public: \
	static std::string typeName() { return #NAME; }; \
}; 