#pragma once
#include <string>
//template <typename T>
//class TypeNameResolver
//{
//public:
//	std::string typeName() { return "Default"; };
//};
//
//#define REGISTER_TYPENAME(NAME) \
//template<> \
//class TypeNameResolver<NAME> \
//{ \
//public: \
//	static std::string typeName() { return #NAME; }; \
//};

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
