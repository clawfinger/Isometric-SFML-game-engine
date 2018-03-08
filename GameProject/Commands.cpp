#include "stdafx.h"
#include "Commands.h"

ICommand::~ICommand() {
	int i;
};

std::string SetPathCommand::name()
{
	return TypeNameResolver<SetPathCommand>::typeName();
}

SetPathCommand::SetPathCommand(Actor* unit, int destination)
{
	m_destination = destination;
	m_unit = unit;
}