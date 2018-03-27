#pragma once
#include <string>
#include "..\Actor.h"

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
	virtual ~ICommand() {};
};

class SetPathCommand: public ICommand
{
public:
	~SetPathCommand() {};
	SetPathCommand(Actor* unit, int destination);
	std::string name();
	int m_destination;
	Actor* m_unit;
};
REGISTER_TYPENAME(SetPathCommand)

class ViewMoveCommand : public ICommand
{
public:
	ViewMoveCommand();
	ViewMoveCommand(float x, float y, float speed);
	std::string name();
	float x_direction;
	float y_direction;
	float m_speed;
};
REGISTER_TYPENAME(ViewMoveCommand)
