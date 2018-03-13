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

ViewMoveCommand::ViewMoveCommand(float x, float y, float speed):
	x_movement(x), y_movement(y), m_speed(speed)
{

}

std::string ViewMoveCommand::name()
{
	return TypeNameResolver<ViewMoveCommand>::typeName();
}
