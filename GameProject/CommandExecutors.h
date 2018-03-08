#pragma once
#include <string>
#include <map>
#include <iostream>
#include <memory>
#include "Map.h"
#include "Commands.h"

class ICommand;
class PathFollower;

class ICommandExecutor
{
public:
	virtual void execute(ICommand* command) = 0;
	virtual ~ICommandExecutor() {}
};

class SetPathCommandExecutor : public ICommandExecutor
{
public:
	SetPathCommandExecutor(Map& map): m_map(map)
	{
	};
	void execute(ICommand* command);

private:
	Map& m_map;
};