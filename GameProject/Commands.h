#pragma once
#include <string>
#include "PathFollower.h"

template <typename TCommand>
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
}; \

class ICommand
{
public:
	virtual std::string name() = 0;
	virtual ~ICommand() = 0;
};

class SetPathCommand;
REGISTER_TYPENAME(SetPathCommand)
class SetPathCommand: public ICommand
{
public:
	SetPathCommand(PathFollower* unit, int destination);
	std::string name();
	int m_destination;
	PathFollower* m_unit;
};

std::string SetPathCommand::name()
{
	return TypeNameResolver<SetPathCommand>::typeName();
}

inline SetPathCommand::SetPathCommand(PathFollower* unit, int destination)
{
	m_destination = destination;
	m_unit = unit;
}
