#pragma once
#include <map>
#include <memory>
#include "CommandExecutors.h"
#include "Commands.h"
class Window;

class CommandDispatcher
{
public:
	CommandDispatcher(Map& map, Window& window);
	void execute(ICommand* command);
private:
	std::map<std::string, ICommandExecutor*> m_executors;
};
