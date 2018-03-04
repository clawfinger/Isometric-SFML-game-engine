#include "stdafx.h"
#include "CommandDispatcher.h"

CommandDispatcher::CommandDispatcher()
{
	// create executor and insert to m_executors, key is command.name()

}

void CommandDispatcher::execute(ICommand* command)
{
	if (m_executors.find(command->name()) != m_executors.end())
		m_executors[command->name()]->execute(command);
	else
		std::cout << "ERROR: Cannot find executor for " << command->name() << std::endl;
}

