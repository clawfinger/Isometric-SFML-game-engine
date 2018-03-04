#pragma once
#include <map>
#include <memory>
#include "CommandExecutors.h"
#include "Commands.h"

class CommandDispatcher
{
public:
	CommandDispatcher();
	void execute(ICommand* command);
private:
	std::map<std::string, std::unique_ptr<ICommandExecutor>> m_executors;
};
