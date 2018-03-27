#include "stdafx.h"
#include "Commands.h"

std::string SetPathCommand::name()
{
	return TypeNameResolver<SetPathCommand>::typeName();
}

SetPathCommand::SetPathCommand(Actor* unit, int destination)
{
	m_destination = destination;
	m_unit = unit;
}

ViewMoveCommand::ViewMoveCommand() :
	x_direction(0), y_direction(0), m_speed(0)
{
}

ViewMoveCommand::ViewMoveCommand(float x, float y, float speed):
	x_direction(x), y_direction(y), m_speed(speed)
{

}

std::string ViewMoveCommand::name()
{
	return TypeNameResolver<ViewMoveCommand>::typeName();
}
