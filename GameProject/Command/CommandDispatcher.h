#pragma once
#include <map>
#include <memory>
#include "CommandExecutors.h"
#include "Commands.h"

class CommandDispatcher
{
public:
	CommandDispatcher(Map& map, Window& window);
	~CommandDispatcher();
	void execute(ICommand* command);
private:
	std::map<std::string, ICommandExecutor*> m_executors;
};
